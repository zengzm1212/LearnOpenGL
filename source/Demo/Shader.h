#pragma once

#include <glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include <string>
#include "detail\type_mat.hpp"

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();

	// 使用/激活程序
	void useProgram();

	// uniform工具函数,查询一个unform的位置值并设置它的值
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setVec3(const std::string &name, float v0, float v1, float v2) const;


	std::string GetVertexString() { return m_vertexStr; };
	std::string GetFragmentString() { return m_fragmentStr; };

	unsigned int GetProgramId() { return m_programId; };

private:
	unsigned int m_programId;
	std::string m_vertexStr;
	std::string m_fragmentStr;
};

