#version 330 core
out vec4 FragColor;
  
// 物体本身材质的影响(物体本身的颜色通过材质来体现)
struct Material{
	sampler2D  diffuse;   // 由于物体本身的环境光颜色和漫反射颜色几乎一样，所以可以都用漫反射来代替
	sampler2D  specular;  // 定义了在镜面光照下物体的反射材质
	float shininess;  // 反光度, 影响镜面高光的散射/半径
};

// 定向光
struct DirLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// 点光源
struct PointLight{
	vec3 position;
	
	float constant;
	float liner;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// 聚光灯
struct SpotLight{
	vec3 position;
	vec3 direction;
	
	float cutOff;
	float outerCutOff;
	
	float constant;
	float liner;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NUM_OF_POINT_LLIGHTS   4   // 点光源的数量

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
  
uniform vec3 viewPos;

uniform DirLight dirLight;
uniform PointLight pointLights[NUM_OF_POINT_LLIGHTS];
uniform SpotLight spotLight;

uniform Material material;

// 函数声明
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  //得到定向光照射的结果
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);   // 得到点光源照射的结果
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);   // 得到聚光灯照射的结果

void main()
{
    // 法向
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 result = vec3(0, 0, 0);
	
	// 1、计算平行光影响的结果
	result += CalcDirLight(dirLight, norm, viewDir);
	
	// 2、计算点光源影响的结果
	for(int i = 0; i < NUM_OF_POINT_LLIGHTS; ++i)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}
	
	// 3、计算聚光灯光源影响的结果
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
	
	FragColor = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	// 漫反射光的折算
	float diff = max(dot(light.direction, normal), 0);
	
	// 镜面光的折算
	vec3 reflectDir = reflect(-light.direction, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
		
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * vec3(texture(material.specular, TexCoords));
	
	// 环境光(不做衰减) + 漫反射 + 镜面反射
	return (ambient + diff * diffuse + spec * specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // 光线方向
	vec3 lightDir = normalize(light.position - fragPos);
	
	// 漫反射光的折算
	float diff = max(dot(lightDir, normal), 0);
	
	// 镜面光的折算
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	
	// 点光源随距离的衰减
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.liner * distance + light.quadratic * (distance * distance));
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * vec3(texture(material.specular, TexCoords));
	
	// 环境光(不做衰减) + 漫反射 + 镜面反射
	return attenuation * (ambient + diff * diffuse + spec * specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	// 光线方向
	vec3 lightDir = normalize(light.position - fragPos);
	
	// 漫反射光的折算
	float diff = max(dot(lightDir, normal), 0);
	
	// 镜面光的折算
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	
    // 点光源随距离的衰减
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.liner * distance + light.quadratic * (distance * distance));
	
	// 聚光灯光源
	float theta = dot(lightDir, normalize(-light.direction));  
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * vec3(texture(material.specular, TexCoords));
	
	// 环境光(不做衰减) + 漫反射 + 镜面反射
	return intensity * attenuation * (ambient + diff * diffuse + spec * specular);
}
