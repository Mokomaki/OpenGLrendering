#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Scene.h"


class Renderer
{
public:
	Renderer();
	void Render(Scene* scene);
private:
	void DrawElements(unsigned int indexCount);
	void ApplyUniforms(WorldObject& object, Scene& scene ,Shader& shader);
	void Clear();
private:
	glm::vec4 m_clearColor;
	GLenum m_clearflags;
};
