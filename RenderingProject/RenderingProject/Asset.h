#pragma once
enum class ASSETTYPE
{
	MESH,
	SHADER,
	TEXTURE,
	UNIFORMDATA
};



class Asset
{
public:
	virtual void Bind() =0;
	virtual ASSETTYPE GetAssetType()=0;
	const char* m_name;
};