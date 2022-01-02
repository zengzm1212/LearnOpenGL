#pragma once

#include <string>
#include <vector>
#include <glm.hpp>
#include "Shader.h"

// 顶点
struct Vertex
{
	glm::vec3 m_position;	// 顶点的位置坐标
	glm::vec3 m_normal;		// 顶点的法线方向
	glm::vec2 m_texCoords;	// 顶点的材质坐标

};

// 材质贴图
struct Texture
{
	unsigned int	m_id;    // 材质Id
	std::string		m_type;  // 材质贴图的用途，用于漫反射还是镜面反射
	std::string		m_path;  // 材质贴图的路径
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