#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color)
{
	m_position = position;
	m_color = color;
}
Light::Light()
{
	m_position = glm::vec3(1.0f);
	m_color = glm::vec3(1.0f);
}