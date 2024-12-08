#include "Texture.h"

ASSETTYPE Texture::GetAssetType()
{
	return ASSETTYPE::TEXTURE;
}

Texture::Texture(const char* path, GLenum wrappingMode)
{
	LoadTextureFromFile(path, wrappingMode, 0);
}
Texture::Texture(const char* path)
{
	LoadTextureFromFile(path, GL_REPEAT, 0);
}

Texture::Texture(const char* paths[], GLenum wrappingMode, int numTextures)
{
	if (numTextures > 16)
	{
		std::cout << "ERROR: Cannot load more than 16 textures to a single texture asset!" << std::endl;
		return;
	}
	for (int i = 0; i < numTextures; i++)
	{
		LoadTextureFromFile(paths[i], wrappingMode, i);
	}
}
Texture::Texture(const char* paths[], int numTextures)
{
	if (numTextures > 16)
	{
		std::cout << "ERROR: Cannot load more than 16 textures to a single texture asset!" << std::endl;
		return;
	}
	for (int i = 0; i < numTextures; i++)
	{
		LoadTextureFromFile(paths[i], GL_REPEAT, i);
	}
}

void Texture::Bind()
{
	for (int i = 0; i < m_textureIDs.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textureIDs[i]);
	}
}

void Texture::LoadTextureFromFile(const char* path, GLenum wrappingMode, int index)
{
	int width = 0, height = 0, channelCount = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &channelCount, 0);

	m_textureIDs.emplace_back(0);
	
	glGenTextures(1, &m_textureIDs[index]);
	glBindTexture(GL_TEXTURE_2D, m_textureIDs[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (channelCount == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (channelCount == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}