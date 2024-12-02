#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	Light();
public:
	glm::vec3 m_position;
	glm::vec3 m_color;
};