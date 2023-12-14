#pragma once
#include "Object.h"
#include "Texture.h"
#include "Ground.h"

class MapObject : public Ground
{
public:
	MapObject();
	~MapObject();
public:
	void DeepCopy(MapObject* rhs);
	void Render(HDC _dc) override;
	virtual void EnterCollision(Collider* other) override;
	virtual void StayCollision(Collider* other) override;
	virtual void ExitCollision(Collider* other) override;
};

