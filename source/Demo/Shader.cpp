#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Demo.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	:m_programId(-1)
{
	// step 1: read shader code from file
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);  // 逻辑上打不开文档，物理上打不开文档
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// 打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		// 从 stream 转到 string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "failed to read file" << std::endl;
	}

	m_vertexStr = vertexCode;
	m_fragmentStr = fragmentCode;

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	// step 2: compile shader
	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

	// vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "failed to compile vertex shader: " << infoLog << std::endl;
	};

	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);            // create a shader
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);   // input code to shader
	glCompileShader(fragmentShader);                                // compile shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);     // check for shader compile error
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "failed to compile fragment shader: " << infoLog << std::endl;
	}

	// step 3: link program
	m_programId = glCreateProgram();
	glAttachShader(m_programId, vertexShader);
	glAttachShader(m_programId, fragmentShader);
	glLinkProgram(m_programId);

	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
		std::cout << "failed to link program: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::useProgram()
{
	glUseProgram(m_programId);
}

void Shader::setBool(const std::string &name, bool value) const
{
	GLint valueLocation = glGetUniformLocation(m_programId, name.c_str());
	glUniform1i(valueLocation, int(value));
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	//float timeValue = float(glfwGetTime());
	//float red = 0.0f;
	//float green = sin(timeValue) / 2.0f + 0.5f;
	//float blue = 0.0f;
	//float alpha = 1.0f;
	//int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
	//glUniform4f(vertexColorLocation, red, green, blue, alpha);

	glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat) /*&mat[0][0]*/);
}

void Shader::setVec3(const std::string &name, float v0, float v1, float v2) const
{
	glUniform3f(glGetUniformLocation(m_programId, name.c_str()), v0, v1, v2);
}

void Shader::setVec3(const std::string &name, const glm::vec3& vec) const
{
	glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &vec[0]);
}