#pragma once

#include <string>
#include <vector>
#include "Shader.h"
#include "Mesh.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

class Model
{
public:
	Model(const std::string& path, bool gamma = false);

	void Draw(Shader& shader);

private:
	void LoadModel(const std::string& path);

	void ProcessNode(const aiScene *scene, aiNode *node);

	Mesh ProcessMesh(const aiScene *scene, aiMesh *mesh);

	std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(const char *path);
public:
	std::vector<Mesh>			m_meshes;
	std::vector<Texture>		m_loadedTextures;
	std::string					m_modelDirectory;  // 模型文件所在的文件夹
	bool						m_gamma;
private:

};