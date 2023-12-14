#pragma once
#include "Object.h"
#include "MapMgr.h"
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
    bool CheckColDir(Object* otherObj);
public:
    void UpdateState();
    void UpdateMove();
public:
    void SetShell();
    void SetPlayerColInfo(PLAYER_COL_INFO _colInfo) { m_colInfo = _colInfo; }
    const bool& GetShell() { return _shellOn; }
    const PLAYER_STATE& GetCurState() { return m_curState; }
    UINT GetJumpLevel(float& _acc);
private:
    void Jump();
    void DoubleJump();
    //bool CheckGroundCollider();
    void Land();
    void CreateInit();
    void SetShellOff();
    void InitJump() { _jumpPower = -550.f; }
    void ReStart() { m_vPos = MapMgr::GetInst()->GetSpawnPoint(); }
    //void SetOffSetPos(Vec2 _offsetPos) { m_offsetPos = _offsetPos; }
private:
    float _isCreateEnd;
    float _jumpTime;
    float _curTime;
    bool _shellOn;
    bool _isJump;
    bool _isDoubleJump;
    float _jumpPower;
    bool _isGround;
    float _dir;
    UINT _jumpLevel;
    std::shared_ptr<Texture> m_pTex;
    std::shared_ptr<Texture> m_idleTex;
    PLAYER_STATE m_curState;
    PLAYER_COL_INFO m_colInfo;
};

