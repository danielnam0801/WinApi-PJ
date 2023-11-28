#pragma once
#include "Object.h"
#include "Texture.h"
class MapObject : public Object
{
public:
	MapObject();
	~MapObject();
	void Render(HDC _dc);
private:
	MAPOBJECT_TYPE m_type;
};

