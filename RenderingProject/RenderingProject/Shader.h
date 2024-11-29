#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	~Shader();
	bool IsInitialized();
	void GenerateShader(const char* path);
	void Bind();
	void SetUniform(const std::string& name, glm::mat4& value);
	void SetUniform(const std::string& name, glm::vec3& value);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, bool value);
	void SetUniformTransfrom(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
private:
	void LoadShaderFromFile(const char* path);
	void CheckShaderError(unsigned int shaderID, GLenum process);
	unsigned int GetUniformLocation(const char* name);
private:
	bool m_isInitialized = false;
	std::string m_vertexSource;
	std::string m_fragmentSource;
	unsigned int m_vertexShaderID;
	unsigned int m_fragmentShaderID;
	unsigned int m_programID;

	std::unordered_map<const char*, unsigned int> m_uniformLocations;
	unsigned int m_modelUnifromLocation;
	unsigned int m_viewUnifromLocation;
	unsigned int m_projectionUnifromLocation;
};