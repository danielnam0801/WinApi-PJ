#pragma once
#include "Scene.h"

class Texture;
class Start_Scene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
private:
    std::shared_ptr<Texture> m_Texture;
};

