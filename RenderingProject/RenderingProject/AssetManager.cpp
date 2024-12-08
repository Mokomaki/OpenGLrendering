#include "AssetManager.h"

AssetManager& AssetManager::Instance()
{
	if (s_instance == nullptr)
		s_instance = new AssetManager();
	return *s_instance;
}

AssetManager::AssetManager()
{
	m_runningID = 0;
}

unsigned int AssetManager::ImpLoadShader(std::string path, std::string name)
{
	m_runningID++;
	m_shaders.emplace(m_runningID, new Shader(path.c_str(),true));
	m_shaders[m_runningID]->m_ID = m_runningID;
	m_shaders[m_runningID]->m_name = name.c_str();
	m_nameToID[name] = m_runningID;
	return m_runningID;
}

unsigned int AssetManager::ImpLoadMesh(std::string path, std::string name)
{
	m_runningID++;
	m_meshes.emplace(m_runningID, new Mesh(path.c_str()));
	m_meshes[m_runningID]->m_ID = m_runningID;
	m_meshes[m_runningID]->m_name = name.c_str();
	m_nameToID[name] = m_runningID;
	return m_runningID;
}

unsigned int AssetManager::ImpLoadTexture(std::string path, std::string name)
{
	m_runningID++;
	m_textures.emplace(m_runningID,new Texture(path.c_str()));
	m_textures[m_runningID]->m_ID = m_runningID;
	m_textures[m_runningID]->m_name = name.c_str();
	m_nameToID[name] = m_runningID;
	return m_runningID;
}

Shader& AssetManager::ImpGetShader(unsigned int ID)
{
	return *m_shaders[ID];
}

Mesh& AssetManager::ImpGetMesh(unsigned int ID)
{
	return *m_meshes[ID];
}

Texture& AssetManager::ImpGetTexture(unsigned int ID)
{
	return *m_textures[ID];
}

Shader& AssetManager::ImpGetShader(std::string name)
{
	return GetShader(m_nameToID[name]);
}
Mesh& AssetManager::ImpGetMesh(std::string name)
{
	return GetMesh(m_nameToID[name]);
}
Texture& AssetManager::ImpGetTexture(std::string name)
{
	return GetTexture(m_nameToID[name]);
}

AssetManager* AssetManager::s_instance = nullptr;

unsigned int AssetManager::LoadShader(std::string path, std::string name)
{
	return AssetManager::Instance().ImpLoadShader(path, name);
}

unsigned int AssetManager::LoadMesh(std::string path, std::string name)
{
	return AssetManager::Instance().ImpLoadMesh(path, name);
}
unsigned int AssetManager::LoadTexture(std::string path, std::string name)
{
	return AssetManager::Instance().ImpLoadTexture(path, name);
}
Shader& AssetManager::GetShader(unsigned int ID)
{
	return AssetManager::Instance().ImpGetShader(ID);
}
Mesh& AssetManager::GetMesh(unsigned int ID)
{
	return AssetManager::Instance().ImpGetMesh (ID);
}
Texture& AssetManager::GetTexture(unsigned int ID)
{
	return AssetManager::Instance().ImpGetTexture(ID);
}
Shader& AssetManager::GetShader(std::string name)
{
	return AssetManager::Instance().ImpGetShader(name);
}
Mesh& AssetManager::GetMesh(std::string name)
{
	return AssetManager::Instance().ImpGetMesh(name);
}
Texture& AssetManager::GetTexture(std::string name)
{
	return AssetManager::Instance().ImpGetTexture(name);
}