#pragma once
class MapObject;
class MapFactory
{
public:
	MapObject* CreateMapObj(MAPOBJECT_TYPE _type, Vec2 _spawnPos);
};

