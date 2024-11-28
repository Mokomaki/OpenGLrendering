#include "WorldObject.h"


WorldObject::WorldObject(unsigned int assets[], int size)
{
	m_name = "object";
	for (int i = 0; i < size; i++)
	{
		m_assets.push_back(assets[i]);
	}
}
WorldObject::WorldObject(unsigned int assets[], int size, const char* name)
{
	m_name = name;
	for (int i = 0; i < size; i++)
	{
		m_assets.push_back(assets[i]);
	}
}