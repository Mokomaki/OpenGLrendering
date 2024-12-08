#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <unordered_set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class WorldObject
{
public:
	const char* m_name;
	WorldObject(const char* name);
	void AssociateWithUniform(const char* uniformname);
	void AssociateWithAsset(const char* assetname);
	WorldObject& Translate(glm::vec3 translation);
	WorldObject& Rotate(glm::vec3 axis, float deg);
	WorldObject& Scale(glm::vec3 scalar);
	glm::mat4 m_transform = glm::mat4(1.0f);
	std::vector<const char*> m_assets;

	std::unordered_set<const char*> m_uniformData;
};