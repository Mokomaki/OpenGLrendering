#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


enum class UNIFORMDATATYPE
{
	FLOAT,
	INT,
	BOOL,
	VEC3,
	MAT4,
	PbrProperty
};

struct PbrProperties {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float smoothness;
};

class UniformData
{
public:
	UniformData(const char* name, float value);
	UniformData(const char* name, int value);
	UniformData(const char* name, bool value);
	UniformData(const char* name, glm::vec3 value);
	UniformData(const char* name, glm::mat4 value);
	UniformData(const char* name, PbrProperties value);

	void GetUniformValue(float& out);
	void GetUniformValue(int& out);
	void GetUniformValue(bool& out);
	void GetUniformValue(glm::vec3& out);
	void GetUniformValue(glm::mat4& out);
	void GetUniformValue(PbrProperties& out);

	void SetUniformValue(float value);
	void SetUniformValue(int value);
	void SetUniformValue(bool value);
	void SetUniformValue(glm::vec3 value);
	void SetUniformValue(glm::mat4 value);
	void SetUniformValue(PbrProperties value);

	const char* GetUniformName();
	UNIFORMDATATYPE GetUniformType();
private:
	const char* m_dataName;
private:
	UNIFORMDATATYPE m_type;
	float m_valuef;
	int m_valuei;
	bool m_valueb;
	glm::vec3 m_valuev3;
	glm::mat4 m_valuem4;
	PbrProperties m_valuepbr;
};