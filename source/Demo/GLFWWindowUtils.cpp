#include "GLFWWindowUtils.h"
#include "glfw3.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  // 这个头文件需要放到 STB_IMAGE_IMPLEMENTATION 宏定义后面


GLFWwindow* GLFWWindowUtils::CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, std::string& errorMessage)
{
	InitGlfw();

	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
	if (window == nullptr)
	{
		errorMessage = "Failed to create GLFW window";
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		errorMessage = "Failed to initialize GLAD";
		return nullptr;
	}

	return window;
}

unsigned int GLFWWindowUtils::LoadTexture(const std::string& textureFilePath, std::string& errorMessage)
{
	unsigned int textureBuffer;
	glGenTextures(1, &textureBuffer);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	// 为当前绑定的纹理对象设置环绕过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;// nrChannels: 颜色通道个数
	unsigned char *data = stbi_load(textureFilePath.c_str(), &width, &height, &nrChannels, 0); // awesomeface.png  container.jpg
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);  // 为当前绑定的纹理自动生成所有需要的多级渐远纹理
	}
	else
	{
		errorMessage = "Failed to load texture";
	}
	stbi_image_free(data);
	return textureBuffer;
}

void GLFWWindowUtils::InitGlfw()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      // main version of openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      // minor version of openGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}