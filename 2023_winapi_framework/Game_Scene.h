#pragma once
#include "Scene.h"
class Game_Scene :
    public Scene
{
public:
    virtual void Init() override;
    void Restart();
};

