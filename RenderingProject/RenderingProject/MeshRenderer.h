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


class MeshRenderer
{
public:
	void Initialize(Mesh* mesh, Shader* shader);
	void Draw();
	void SetTexture(Texture* texture);
	void SetShaderUniformFloat(const std::string& name, float value);
	void SetShaderUniformInt(const std::string& name, int value);
	void SetShaderUniformBool(const std::string& name, bool value);
	void SetTransformation(glm::mat4& transfrorm);
private:
	unsigned int m_vertexArrayID, m_vertexBufferID, m_elementBufferID;
	Mesh* m_mesh;
	Shader* m_shader;
	std::vector<Texture> m_textures;
};