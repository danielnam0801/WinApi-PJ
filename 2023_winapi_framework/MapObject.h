#pragma once
#include "Object.h"
#include "Texture.h"
class MapObject : public Object
{
public:
	MapObject();
	~MapObject();
public:
	void DeepCopy(MapObject* rhs);
	void Render(HDC _dc) override;
};

