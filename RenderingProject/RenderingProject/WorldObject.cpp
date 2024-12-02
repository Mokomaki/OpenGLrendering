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
