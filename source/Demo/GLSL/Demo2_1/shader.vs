#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;

out vec2 ourTextureCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0f);
	ourTextureCoord = vec2(aTextureCoord.x, 1-aTextureCoord.y);
}