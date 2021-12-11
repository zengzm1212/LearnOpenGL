#pragma once

#include <glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <string>

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

	std::string GetVertexString() { return m_vertexStr; };
	std::string GetFragmentString() { return m_fragmentStr; };

	unsigned int GetProgramId() { return m_programId; };

private:
	unsigned int m_programId;
	std::string m_vertexStr;
	std::string m_fragmentStr;
};

