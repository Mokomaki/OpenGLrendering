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

#include "UniformData.h"
#include "Asset.h"

class Shader : public Asset
{
public:
	friend class Material;
	Shader(const char* path, bool isShaderLit);
	~Shader();
	void Bind() override;
	ASSETTYPE GetAssetType() override;
	bool IsLitShader() const;
	void SetUniform(const std::string& name, glm::mat4& value);
	void SetUniform(const std::string& name, glm::vec3& value);
	void SetUniform(const std::string& name, glm::mat3& value);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, bool value);
	void SetUniform(PbrProperties& value);
	void SetUniformTransfrom(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
private:
	void GenerateShader(const char* path);
	bool IsInitialized();
	void LoadShaderFromFile(const char* path);
	void CheckShaderError(unsigned int shaderID, GLenum process);
	unsigned int GetUniformLocation(const std::string& name) const;
private:
	bool m_isInitialized;
	bool m_isShaderLit;
	std::string m_vertexSource;
	std::string m_fragmentSource;
	unsigned int m_vertexShaderID;
	unsigned int m_fragmentShaderID;
	unsigned int m_programID;

	mutable std::unordered_map<std::string, unsigned int> m_uniformLocations;
	unsigned int m_modelUnifromLocation;
	unsigned int m_viewUnifromLocation;
	unsigned int m_projectionUnifromLocation;
};