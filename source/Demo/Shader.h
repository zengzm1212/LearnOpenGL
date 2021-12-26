#pragma once

#include <glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <string>
#include "detail\type_mat.hpp"

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();

	// ʹ��/�������
	void useProgram();

	// uniform���ߺ���,��ѯһ��unform��λ��ֵ����������ֵ
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

