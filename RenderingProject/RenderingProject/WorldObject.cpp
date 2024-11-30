#include "WorldObject.h"


WorldObject::WorldObject(const char* assets[], int size)
{
	m_name = "object";
	//m_assets.reserve(size);
	for (int i = 0; i < size; i++)
	{
		m_assets.push_back(assets[i]);
	}
}
WorldObject::WorldObject(const char* assets[], int size, const char* name)
{
	m_name = name;
	//m_assets.reserve(size);
	for (int i = 0; i < size; i++)
	{
		m_assets.push_back(assets[i]);
	}
}
WorldObject::WorldObject(const char* asset0, const char* asset1, const char* asset2)
{
	m_name = "object";
	//m_assets.reserve(3);
	m_assets.push_back(asset0);
	m_assets.push_back(asset1);
	m_assets.push_back(asset2);
}
WorldObject::WorldObject(const char* asset0, const char* asset1, const char* asset2, const char* name)
{
	m_name = name;
	//m_assets.reserve(3);
	m_assets.push_back(asset0);
	m_assets.push_back(asset1);
	m_assets.push_back(asset2);
}

void WorldObject::AssociateWithUniform(const char* uniformname)
{
	m_uniformData.insert(uniformname);
}
