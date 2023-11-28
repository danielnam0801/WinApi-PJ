#include "pch.h"
#include "MapObject.h"
#include "Collider.h"

MapObject::MapObject()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(1000.f, 100.f));
}

MapObject::~MapObject()
{
}

void MapObject::Render(HDC _dc)
{
	Component_Render(_dc);
}
