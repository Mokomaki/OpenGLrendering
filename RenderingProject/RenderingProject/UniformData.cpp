#include "UniformData.h"

UniformData::UniformData(const char* name, float value)
{
	m_dataName = name;
	m_type = UNIFORMDATATYPE::FLOAT;
	m_valuef = value;
	m_valuei = 0;
	m_valueb = false;
	m_valuev3 = glm::vec3(1.0f);
	m_valuem4 = glm::mat4(1.0f);
}

UniformData::UniformData(const char* name, int value)
{
	m_dataName = name;
	m_type = UNIFORMDATATYPE::INT;
	m_valuei = value;
	m_valuef = 0.0f;
	m_valueb = false;
	m_valuev3 = glm::vec3(1.0f);
	m_valuem4 = glm::mat4(1.0f);
}

UniformData::UniformData(const char* name, bool value)
{
	m_dataName = name;
	m_type = UNIFORMDATATYPE::BOOL;
	m_valueb = value;
	m_valuef = 0.0f;
	m_valuei = 0;
	m_valuev3 = glm::vec3(1.0f);
	m_valuem4 = glm::mat4(1.0f);
}

UniformData::UniformData(const char* name, glm::vec3 value)
{
	m_dataName = name;
	m_type = UNIFORMDATATYPE::VEC3;
	m_valuev3 = value;
	m_valuef = 0.0f;
	m_valuei = 0;
	m_valueb = false;
	m_valuem4 = glm::mat4(1.0f);
}

UniformData::UniformData(const char* name, glm::mat4 value)
{
	m_dataName = name;
	m_type = UNIFORMDATATYPE::MAT4;
	m_valuem4 = value;
	m_valuef = 0.0f;
	m_valuei = 0;
	m_valueb = false;
	m_valuev3 = glm::vec3(1.0f);
}

UniformData::UniformData(const char* name, PbrProperties value)
{
	m_dataName = name;
	m_type = UNIFORMDATATYPE::PbrProperty;
	m_valuepbr = value;
	m_valuef = 0.0f;
	m_valuei = 0;
	m_valueb = false;
	m_valuev3 = glm::vec3(1.0f);
	m_valuem4 = glm::mat4(1.0f);
}

void UniformData::GetUniformValue(float& out)
{
	out = m_valuef;
}

void UniformData::GetUniformValue(int& out)
{
	out = m_valuei;
}

void UniformData::GetUniformValue(bool& out)
{
	out = m_valueb;
}

void UniformData::GetUniformValue(glm::vec3& out)
{
	out = m_valuev3;
}

void UniformData::GetUniformValue(glm::mat4& out)
{
	out = m_valuem4;
}

void UniformData::GetUniformValue(PbrProperties& out)
{
	out = m_valuepbr;
}

void UniformData::SetUniformValue(float value)
{
	m_valuef = value;
}

void UniformData::SetUniformValue(int value)
{
	m_valuei = value;
}

void UniformData::SetUniformValue(bool value)
{
	m_valueb = value;
}

void UniformData::SetUniformValue(glm::vec3 value)
{
	m_valuev3 = value;
}

void UniformData::SetUniformValue(glm::mat4 value)
{
	m_valuem4 = value;
}

void UniformData::SetUniformValue(PbrProperties value)
{
	m_valuepbr = value;
}

const char* UniformData::GetUniformName()
{
	return m_dataName;
}

UNIFORMDATATYPE UniformData::GetUniformType()
{
	return m_type;
}