#version 330 core
out vec4 FragColor;
  
// 物体本身材质的影响(物体本身的颜色通过材质来体现)
struct Material{
	sampler2D  diffuse;   // 由于物体本身的环境光颜色和漫反射颜色几乎一样，所以可以都用漫反射来代替
	sampler2D  specular;  // 定义了在镜面光照下物体的反射材质
	float shininess;  // 反光度, 影响镜面高光的散射/半径
};

// 光源的影响
struct Light{
    vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
  
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main()
{
    // ambient 环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
    // diffuse 漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);  // 从物体指向光源的方向
    float diff = max(dot(norm, lightDir), 0.0);     // 法向和光源方向的点积，得到漫反射对光的衰减
    vec3 diffuse =  light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	// specular 镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);   // 从物体到眼睛的方向
    vec3 reflectDir = reflect(-lightDir, norm);    // 反射光的方向（取反是因为反射和镜像不一样）
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // material.shininess 是反光度，反光度越高，反射能力越强，散射的越少
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
	
	vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}