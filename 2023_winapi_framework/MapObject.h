#pragma once
#include "Object.h"
#include "Texture.h"
class MapObject : public Object
{
public:
	MapObject(MAPOBJECT_TYPE type);
	~MapObject();
private:
	MAPOBJECT_TYPE m_type;
};

