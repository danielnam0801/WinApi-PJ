#pragma once
#include "Object.h"
#include "Texture.h"
class Background : public Object
{
public:
	Background();
	~Background();
public:
	void Render(HDC _dc) override;
};

