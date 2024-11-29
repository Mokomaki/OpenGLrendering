#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Asset.h"


enum class UNIFORMDATATYPE
{
	FLOAT,
	INT,
	BOOL,
	VEC3,
	MAT4
};

class UniformData : public Asset
{
public:
	UniformData(const char* name, float value);
	UniformData(const char* name, int value);
	UniformData(const char* name, bool value);
	UniformData(const char* name, glm::vec3 value);
	UniformData(const char* name, glm::mat4 value);
	void GetUniformValue(float& out);
	void GetUniformValue(int& out);
	void GetUniformValue(bool& out);
	void GetUniformValue(glm::vec3& out);
	void GetUniformValue(glm::mat4& out);
	void SetUniformValue(float& value);
	void SetUniformValue(int& value);
	void SetUniformValue(bool& value);
	void SetUniformValue(glm::vec3& value);
	void SetUniformValue(glm::mat4& value);
	const char* GetUniformName();
	UNIFORMDATATYPE GetUniformType();
	ASSETTYPE GetAssetType() override;
	void Bind() override;
public:
	const char* m_name;
private:
	UNIFORMDATATYPE m_type;
	float m_valuef;
	int m_valuei;
	bool m_valueb;
	glm::vec3 m_valuev3;
	glm::mat4 m_valuem4;
};