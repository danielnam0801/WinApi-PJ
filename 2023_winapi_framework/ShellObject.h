#pragma once

#include "Object.h"
class ShellObject : public Object
{
public:
	ShellObject();
	~ShellObject();
public:
	void DeepCopy(ShellObject* rhs);
	void Render(HDC _dc) override;
};

