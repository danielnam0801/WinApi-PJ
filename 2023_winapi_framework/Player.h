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
    void CreateInit();
    //void SetOffSetPos(Vec2 _offsetPos) { m_offsetPos = _offsetPos; }
private:
    float _isCreateEnd;
    float _jumpTime;
    float _curTime;
    bool _isJump;
    bool _isDoubleJump;
    float _jumpPower;
    bool _isGround;
    Vec2 _moveDir;
    std::shared_ptr<Texture> m_pTex;
    std::shared_ptr<Texture> m_idleTex;
};

