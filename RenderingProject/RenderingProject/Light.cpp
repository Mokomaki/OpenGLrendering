#include "Light.h"
/*
Light::Light(glm::vec3 position, glm::vec3 color)
{
	m_position = position;
	m_color = color;
}
Light::Light()
{
	m_position = glm::vec3(1.0f);
	m_color = glm::vec3(1.0f);
}*/

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color)
{
	m_direction = direction;
	m_color = color;
}
DirectionalLight::DirectionalLight()
{
	m_direction = glm::vec3(1.0f,-1.0f,-1.0f);
	m_color = glm::vec3(1.0f);
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float range)
{
	m_position = position;
	m_color = color;

	m_constantAttennuationTerm = 1.0f;
	if (range < 7.1f)
	{
		m_linearAttennuationTerm = 0.7f;
		m_quadraticAttennuationTerm = 1.8f;
	}
	else if (range < 13.1f)
	{
		m_linearAttennuationTerm = 0.35f;
		m_quadraticAttennuationTerm = 0.44f;
	}
	else if (range < 20.1f)
	{
		m_linearAttennuationTerm = 0.22f;
		m_quadraticAttennuationTerm = 0.20f;
	}
	else if (range < 32.1f)
	{
		m_linearAttennuationTerm = 0.14f;
		m_quadraticAttennuationTerm = 0.07f;
	}
	else if (range < 50.1f)
	{
		m_linearAttennuationTerm = 0.09f;
		m_quadraticAttennuationTerm = 0.032;
	}
	else if (range < 65.1f)
	{
		m_linearAttennuationTerm = 0.07f;
		m_quadraticAttennuationTerm = 0.017f;
	}
	else if (range < 100.1f)
	{
		m_linearAttennuationTerm = 0.045f;
		m_quadraticAttennuationTerm = 0.0075f;
	}
	else if (range < 160.1f)
	{
		m_linearAttennuationTerm = 0.027f;
		m_quadraticAttennuationTerm = 0.0028f;
	}
	else if (range < 200.1f)
	{
		m_linearAttennuationTerm = 0.022f;
		m_quadraticAttennuationTerm = 0.0019f;
	}
	else if (range < 325.1f)
	{
		m_linearAttennuationTerm = 0.014f;
		m_quadraticAttennuationTerm = 0.0007f;
	}
	else if (range < 600.1f)
	{
		m_linearAttennuationTerm = 0.007f;
		m_quadraticAttennuationTerm = 0.0002f;
	}
	else if (range < 3250.1f)
	{
		m_linearAttennuationTerm = 0.0014f;
		m_quadraticAttennuationTerm = 0.000007f;
	}
	else
	{
		m_linearAttennuationTerm = 0.0001f;
		m_quadraticAttennuationTerm = 0.0000001f;
	}
}
PointLight::PointLight()
{
	m_position = glm::vec3(1.0f);
	m_color = glm::vec3(1.0f);
	//default range 32
	m_constantAttennuationTerm = 1.0f;
	m_linearAttennuationTerm = 0.14f;
	m_quadraticAttennuationTerm = 0.07f;
}