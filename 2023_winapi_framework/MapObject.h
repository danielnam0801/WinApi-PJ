#pragma once
#include "Object.h"
#include "Texture.h"
class MapObject : public Object
{
public:
	MapObject();
	~MapObject();
public:
	void Render(HDC _dc) override;
private:
	MAPOBJECT_TYPE m_type;
};

