#include "WorldObject.h"


WorldObject::WorldObject(const char* name)
{
	m_name = name;
}

void WorldObject::AssociateWithUniform(const char* uniformname)
{
	m_uniformData.insert(uniformname);
}

void WorldObject::AssociateWithAsset(const char* assetname)
{
	m_assets.push_back(assetname);
}

WorldObject& WorldObject::Translate(glm::vec3 translation)
{
	m_transform = glm::translate(m_transform, translation);
	return *this;
}

WorldObject& WorldObject::Rotate(glm::vec3 axis, float deg)
{
	m_transform = glm::rotate(m_transform, glm::radians(deg), axis);
	return *this;
}

WorldObject& WorldObject::Scale(glm::vec3 scalar)
{
	m_transform = glm::scale(m_transform, scalar);
	return *this;
}