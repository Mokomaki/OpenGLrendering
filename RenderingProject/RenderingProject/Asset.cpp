#include "Asset.h"

//Texture constructor
Asset::Asset(const char* texturePaths[], unsigned int assetID, unsigned short numTextures)
{
	if (numTextures > 16)
	{
		std::cout << "ERROR: Cannot have an asset with more than 16 textures!" << std::endl;
		return;
	}
	m_type = AssetType::TEXTURE;
	m_ID = assetID;
	
	for (int i = 0; i < numTextures; i++)
	{
		m_textures.push_back(Texture(texturePaths[i]));
	}
}
//Shader constructor
Asset::Asset(const char* shaderPath, unsigned int assetID)
{
	m_type = AssetType::SHADER;
	m_ID = assetID;
	m_shader.GenerateShader(shaderPath);
}
//Mesh constructor
Asset::Asset(PrimitiveMeshShapes meshPrimitive, unsigned int assetID)
{
	m_type = AssetType::MESH;
	m_ID = assetID;
	m_mesh.CreatePrimitive(meshPrimitive);
	m_mesh.InitBuffers();
}
void Asset::Bind()
{
	switch (m_type)
	{
	case AssetType::MESH:
		m_mesh.Bind();
		break;
	case AssetType::SHADER:
		m_shader.Bind();
		break;
	case AssetType::TEXTURE:
		break;
	default:
		for (int i = 0; i < m_textures.size(); i++)
		{
			m_textures[i].Bind(i);
		}
		break;
	}
}

void Asset::SetTransformation(glm::mat4 transformation)
{
	if (m_type != AssetType::SHADER)
	{
		std::cout << "ERROR: Attempted to set transform for non-shader asset!" << std::endl;
		return;
	}

	m_shader.SetUniformTransfrom(transformation);
}

unsigned int Asset::GetIndexCount()
{
	if (m_type != AssetType::MESH)
	{
		std::cout << "ERROR: Attemted to retrive indexcount from non-mesh asset!" << std::endl;
		return 0;
	}
	return m_mesh.GetIndexCount();
}

AssetType Asset::GetAssetType()
{
	return m_type;
}
unsigned int Asset::GetID()
{
	return m_ID;
}