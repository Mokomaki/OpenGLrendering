#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

enum class AssetType
{
	MESH,
	SHADER,
	TEXTURE
};

class Asset
{
public:
	Asset(const char* texturePaths[], unsigned int assetID, unsigned short numTextures);
	Asset(const char* shaderPath, unsigned int assetID);
	Asset(PrimitiveMeshShapes meshPrimitive, unsigned int assetID);
	void Bind();
	AssetType GetAssetType();
	unsigned int GetID();
	void SetTransformation(glm::mat4 transformation);
	unsigned int GetIndexCount();
private:
	unsigned int m_ID;
	AssetType m_type;
	Mesh m_mesh;
	Shader m_shader;
	std::vector<Texture> m_textures;
};