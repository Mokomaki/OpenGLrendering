#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>

#include "stb_image.h"

class Texture
{
public:
	Texture(const char* path, GLenum wrappingMode);
	Texture(const char* path);
	void Bind(unsigned short textureUnit);
private:
	int m_width, m_height, m_channelCount;
	unsigned int m_textureID;
};