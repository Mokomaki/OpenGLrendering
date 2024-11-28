#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class WorldObject
{
public:
	const char* m_name;
	WorldObject(unsigned int assets[], int size);
	WorldObject(unsigned int assets[], int size,const char* name);
	glm::mat4 m_transform = glm::mat4(1.0f);
	std::vector<unsigned int> m_assets;
};