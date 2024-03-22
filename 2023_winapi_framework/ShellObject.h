#pragma once

#include "Object.h"
class ShellObject : public Object
{
public:
	ShellObject();
	~ShellObject();
public:
	void Update();
	void Render(HDC _dc) override;
	void EnterCollision(Collider* _pOther) override;
public:
	void Reload();
public:
	Vec2 spawnPoint;
private:
	bool enabled;
};

