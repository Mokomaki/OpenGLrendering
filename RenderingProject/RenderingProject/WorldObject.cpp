#include "WorldObject.h"


WorldObject::WorldObject(unsigned int assets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		m_assets.push_back(assets[i]);
	}
}