#version 330 core
out vec4 FragColor;

in vec2 ourTextureCoord;

uniform sampler2D inputBoxTexture;
uniform sampler2D inputFaceTexture;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	//FragColor = vec4(objectColor * lightColor, 1.0f);
	FragColor = vec4(objectColor * lightColor, 1.0f) * mix(texture(inputBoxTexture, ourTextureCoord), texture(inputFaceTexture, ourTextureCoord), 0.2);
}