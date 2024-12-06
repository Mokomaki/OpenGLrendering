#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WorldObject.h"
#include "Asset.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "UniformData.h"
#include "Camera.h"
#include "Light.h"

class Scene
{
public:
	void Initialize();
	WorldObject& CreateWorldObect(const char* name);
	DirectionalLight& CreateLightDirectional(glm::vec3 direction, glm::vec3 color);
	PointLight& CreateLightPoint(glm::vec3 position, glm::vec3 color,float range);
	WorldObject* GetWorldObjectByName(const char* name);
	std::vector<WorldObject*> GetWorldObjectsWithName(const char* name);
public:
	Camera* m_camera;
	std::vector<WorldObject> m_objects;
	std::vector<DirectionalLight> m_directionalLights;
	std::vector<PointLight> m_pointLights;
	std::unordered_map<const char*,Asset*> m_assets;
	std::unordered_map<const char*, UniformData*> m_uniformdata;
};