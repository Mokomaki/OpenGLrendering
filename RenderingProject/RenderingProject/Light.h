#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	Light();
public:
	glm::vec3 m_position;
	glm::vec3 m_color;
};*/

class DirectionalLight
{
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color);
	DirectionalLight();
public:
	glm::vec3 m_direction;
	glm::vec3 m_color;
};

class PointLight
{
public:
	PointLight(glm::vec3 position, glm::vec3 color, float range);
	PointLight();
public:
	glm::vec3 m_color;
	glm::vec3 m_position;
	float m_constantAttennuationTerm;
	float m_linearAttennuationTerm;
	float m_quadraticAttennuationTerm;
};