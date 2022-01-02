#pragma once

#include <string>
#include <vector>
#include <glm.hpp>
#include "Shader.h"

// ����
struct Vertex
{
	glm::vec3 m_position;	// �����λ������
	glm::vec3 m_normal;		// ����ķ��߷���
	glm::vec2 m_texCoords;	// ����Ĳ�������

};

// ������ͼ
struct Texture
{
	unsigned int	m_id;    // ����Id
	std::string		m_type;  // ������ͼ����;�����������仹�Ǿ��淴��
	std::string		m_path;  // ������ͼ��·��
};

class Mesh {
public:
	Mesh(float vertices[]);
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);

	void Draw(Shader& shader);

private:
	void SetupMesh();

public:
	std::vector<Vertex>			m_vertices;
	std::vector<unsigned int>   m_indices;
	std::vector<Texture>		m_textures;
	unsigned int				m_VAO;
	unsigned int				m_VBO;
	unsigned int				m_EBO;
private:

};