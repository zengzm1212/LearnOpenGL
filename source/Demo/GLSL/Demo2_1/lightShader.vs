#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // FragPos 物体的实际位置，乘位移矩阵之后的位置
    FragPos = vec3(model * vec4(aPos, 1.0f));
	
	// 把法向量转成世界坐标系中的法向量，但是只乘model矩阵的话，不等比缩放的情况会影响到法线方向不再和平面垂直
    // 由于求逆矩阵的操作比较耗时，最好是在CPU中将该矩阵计算好，再传给着色器（uniform）
	Normal = mat3(transpose(inverse(model))) * aNormal;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}