#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>

#include "stb_image.h"

class Texture
{
public:
	void Initialize(const char* path, GLenum wrappingMode);
	void Bind(unsigned short textureUnit);
private:
	int m_width, m_height, m_channelCount;
	unsigned int m_textureID;
};