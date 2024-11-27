#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WorldObject.h"
#include "Asset.h"


class Scene
{
public:
	void Initialize();
public:
	glm::mat4 m_cameraView;
	glm::mat4 m_cameraProjection;
	std::vector<WorldObject*> m_objects;
	std::vector<Asset*> m_assets;
};