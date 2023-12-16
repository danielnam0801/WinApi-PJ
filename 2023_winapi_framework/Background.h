#pragma once
#include "Object.h"
#include "Texture.h"
class Background : public Object
{
public:
	Background(std::shared_ptr<Texture> tex);
	~Background();
public:
	void Render(HDC _dc) override;
};

