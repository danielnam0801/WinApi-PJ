#pragma once

#include "Object.h"
class ShellObject : public Object
{
public:
	ShellObject();
	~ShellObject();
public:
	void Render(HDC _dc) override;
	void EnterCollision(Collider* _pOther) override;
};

