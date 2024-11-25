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

class WorldObject
{
private:
	MeshRenderer m_renderer;
public:
	glm::mat4 m_transform = glm::mat4(1.0f);
	MeshRenderer* GetRenderer() { return &m_renderer; }
	void OnStart();
	void OnUpdate();
};