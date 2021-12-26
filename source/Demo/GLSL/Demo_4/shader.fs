#version 330 core
out vec4 FragColor;

in vec3 ourPostion;
in vec3 ourColor;
in vec2 ourTextureCoord;

uniform sampler2D inputBoxTexture;
uniform sampler2D inputFaceTexture;

void main()
{
    // FragColor = vec4(ourColor, 1.0f);   
	// FragColor = vec4(ourPostion, 1.0f);  
	
	// FragColor = texture(inputBoxTexture, ourTextureCoord) * vec4(ourColor, 1.0);  // 多彩的盒子
	// FragColor = texture(inputFaceTexture, ourTextureCoord);  // 笑脸
	
	// 混合 inputBoxTexture 和 inputFaceTexture 两张图片，以 8:2 混合
	FragColor = mix(texture(inputBoxTexture, ourTextureCoord), texture(inputFaceTexture, ourTextureCoord), 0.2);
	
}