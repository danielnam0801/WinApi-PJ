#include "pch.h"
#include "MapFactory.h"
#include "MapObject.h"

MapObject* MapFactory::CreateMapObj(MAPOBJECT_TYPE _type, Vec2 spawnPos)
{
	MapObject* m_obj;
	switch (_type)
	{
	case MAPOBJECT_TYPE::CIRCLE:
		//m_obj = new MapObject(_type);
		break;
	case MAPOBJECT_TYPE::SQUARE:
		break;
	case MAPOBJECT_TYPE::TRIANGLE:
		break;
	}
	return new MapObject();
}
