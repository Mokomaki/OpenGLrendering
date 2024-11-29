#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <vector>

#include "Asset.h"

class Texture : public Asset
{
public:
	Texture(const char* path, GLenum wrappingMode);
	Texture(const char* path);
	Texture(const char* paths[], GLenum wrappingMode, int numTextures);
	Texture(const char* paths[], int numTextures);
	void Bind() override;
	ASSETTYPE GetAssetType() override;
private:
	void LoadTextureFromFile(const char* path, GLenum wrappingMode, int index);
	std::vector<unsigned int> m_textureIDs;
};