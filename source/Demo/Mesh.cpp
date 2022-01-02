#include "Mesh.h"
#include <glad.h>

Mesh::Mesh(float vertices[])
{
	m_vertices.resize(36);
	memcpy(&m_vertices[0], vertices, 36 * 8 * sizeof(float));

	SetupMesh();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
	: m_vertices(vertices)
	, m_indices(indices)
	, m_textures(textures)
{
	SetupMesh();
}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNum = 1;
	unsigned int specularNum = 1;
	unsigned int normalNum = 1;
	unsigned int heightNum = 1;

	for (unsigned int i = 0; i < m_textures.size(); ++i)
	{
		std::string number;
		std::string textureType = m_textures[i].m_type;
		if (textureType == "texture_diffuse")
			number = std::to_string(diffuseNum++);
		else if (textureType == "texture_specular")
			number = std::to_string(specularNum++);
		else if (textureType == "texture_normal")
			number = std::to_string(normalNum++);
		else if (textureType == "texture_height")
			number = std::to_string(heightNum++);

		shader.setInt(textureType + number, i);  // ����λi ��Ӧ�Ĳ��ʣ����õ�shader������

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i].m_id);
	}
	glActiveTexture(GL_TEXTURE0); // �ָ���Ĭ�ϼ���Ĳ��ʲ�λ

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0); // ���ԭ����VAO���ָ���Ĭ��ֵ
}


void Mesh::SetupMesh()
{
	// ����VAO��VBO��EBO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	// ��Vertex�е����ݻ�ȡ�������ŵ���ͬ�Ĳ�λ
	glEnableVertexAttribArray(0); // ���Է�ǰ��Ҳ���Էź���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_texCoords));

	// ���ԭ����VAO
	glBindVertexArray(0);
}