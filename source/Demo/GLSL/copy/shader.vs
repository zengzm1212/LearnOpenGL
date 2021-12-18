#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;

out vec3 ourPostion;
out vec3 ourColor;
out vec2 ourTextureCoord;

uniform float xOffset;
uniform mat4 transform;  // 外界传入的

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    ourColor = aColor;
	ourPostion = aPos;
	ourTextureCoord = aTextureCoord;
}