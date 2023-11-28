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
    void EnterCollision(Collider* _pOther) override;
    void ExitCollision(Collider* _pOther) override;
    void StayCollision(Collider* _pOther) override;
private:
    void Jump();
    void DoubleJump();
    //bool CheckGroundCollider();
    void Land();
    //void SetOffSetPos(Vec2 _offsetPos) { m_offsetPos = _offsetPos; }
private:
    bool _isJump;
    bool _isDoubleJump;
    float _jumpPower;
    bool _isGround;
    Vec2 _moveDir;
    Texture* m_pTex;
};

