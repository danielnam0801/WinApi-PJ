#pragma once
#include "Object.h"
class Texture;
class Player :
    public Object
{
public:
    Player();
    ~Player();
public:
    void Update() override;
    void Render(HDC _dc) override;
private:
    void Jump();
    void DoubleJump();
    bool CheckGroundCollider(float yValue);
    void Land();
private:
    bool _isJump;
    bool _isDoubleJump;
    float _gravityScale;
    float _jumpPower;
    bool _isGround;
    Vec2 _moveDir;
    Texture* m_pTex;
};

