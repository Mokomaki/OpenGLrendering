#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "WorldObject.h"
#include "Camera.h"
#include "Asset.h"

class Scene
{
public:
	void Initialize();
private:
	std::vector<WorldObject> m_objects;
	std::vector<Asset> m_assets;
	Camera m_camera;

};