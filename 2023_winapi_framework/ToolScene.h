#pragma once
#include "Scene.h"
class ToolScene : public Scene
{
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
};

