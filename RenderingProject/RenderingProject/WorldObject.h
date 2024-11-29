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
	WorldObject(const char* asset0, const char* asset1, const char* asset2, const char* name);
	WorldObject(const char* asset0, const char* asset1, const char* asset2);
	WorldObject(const char* assets[], int size, const char* name);
	WorldObject(const char* assets[], int size);
	glm::mat4 m_transform = glm::mat4(1.0f);
	std::vector<const char*> m_assets;
};