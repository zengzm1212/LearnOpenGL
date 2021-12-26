#pragma once

#include <glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <string>
#include "detail\type_mat.hpp"

struct GLFWwindow;
struct GLFWmonitor;

class GLFWWindowUtils
{
public:
	static GLFWwindow* CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr, std::string& errorMessage = std::string());

	static unsigned int LoadTexture(const std::string& textureFilePath, std::string& errorMessage = std::string());

private:
	static void InitGlfw();
};

