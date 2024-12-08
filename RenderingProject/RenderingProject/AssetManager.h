#pragma once
#include <vector>
#include <unordered_map>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "UniformData.h"


class AssetManager
{
public:
	AssetManager(const AssetManager&) = delete;
	static AssetManager& Instance();
	static unsigned int LoadShader(std::string path, std::string name);
	static unsigned int LoadMesh(std::string path, std::string name);
	static unsigned int LoadTexture(std::string path, std::string name);
	//std::vector<unsigned int> LoadTextures(std::string* paths,int countTextures); NOT IMPLEMENTED / TODO
	static Shader& GetShader(unsigned int ID);
	static Mesh& GetMesh(unsigned int ID);
	static Texture& GetTexture(unsigned int ID);
	static Shader& GetShader(std::string name);
	static Mesh& GetMesh(std::string name);
	static Texture& GetTexture(std::string name);

private:
	AssetManager();
	unsigned int ImpLoadShader(std::string path, std::string name);
	unsigned int ImpLoadMesh(std::string path, std::string name);
	unsigned int ImpLoadTexture(std::string path, std::string name);
	//std::vector<unsigned int> LoadTextures(std::string* paths,int countTextures); NOT IMPLEMENTED / TODO
	Shader& ImpGetShader(unsigned int ID);
	Mesh& ImpGetMesh(unsigned int ID);
	Texture& ImpGetTexture(unsigned int ID);
	Shader& ImpGetShader(std::string name);
	Mesh& ImpGetMesh(std::string name);
	Texture& ImpGetTexture(std::string name);
private:

	unsigned int m_runningID;
	static AssetManager* s_instance;
	std::unordered_map<std::string, unsigned int> m_nameToID;
	std::unordered_map<unsigned int, Shader*> m_shaders;
	std::unordered_map<unsigned int, Mesh*> m_meshes;
	std::unordered_map<unsigned int, Texture*> m_textures;
};