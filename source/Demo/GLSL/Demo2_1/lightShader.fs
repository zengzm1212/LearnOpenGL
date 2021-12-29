#version 330 core
out vec4 FragColor;
  
in vec3 FragPos;
in vec3 Normal;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // ambient 环境光
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	
    // diffuse 漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  // 从物体指向光源的方向
    float diff = max(dot(norm, lightDir), 0.0);     // 法向和光源方向的点积，得到漫反射对光的衰减
    vec3 diffuse = diff * lightColor;
	
	// specular 镜面反射
    float specularStrength = 0.5;   // 取一个系数是为了避免镜面光的影响太大
    vec3 viewDir = normalize(viewPos - FragPos);   // 从物体到眼睛的方向
    vec3 reflectDir = reflect(-lightDir, norm);    // 反射光的方向（取反是因为反射和镜像不一样）
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // 32 是反光度，反光度越高，反射能力越强，散射的越少
    vec3 specular = specularStrength * spec * lightColor;  
	
	vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}