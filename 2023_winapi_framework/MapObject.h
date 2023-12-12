#pragma once
#include "Object.h"
#include "Texture.h"
class MapObject : public Object
{
public:
	MapObject();
	~MapObject();
	MapObject(const MapObject& rhs);
public:
	void DeepCopy(const std::shared_ptr<MapObject>& rhs);
	void Render(HDC _dc) override;
private:
	MAPOBJECT_TYPE m_type;
};

