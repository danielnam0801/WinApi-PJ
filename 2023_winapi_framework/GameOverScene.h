#pragma once

#include "Scene.h"
class GameOverScene
	: public Scene
{
public:
	void GameOver();

	// Scene을(를) 통해 상속됨
	void Init() override;
};

