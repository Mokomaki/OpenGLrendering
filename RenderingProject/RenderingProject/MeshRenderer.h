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
#include "Scene.h"

class MeshRenderer
{
public:
	void Render(Scene* scene);
private:
	void Draw(unsigned int indexCount);
};
