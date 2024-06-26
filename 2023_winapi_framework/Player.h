#pragma once
#include "Object.h"
#include "MapMgr.h"
#include <sstream>
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
    const PLAYER_STATE& GetCurState() { return m_curState; }
    const bool& GetShell() { return _shellOn; }
    const bool& IsCanDetect() { return _isCanDetect; }
    float GetJumpLevel(float& _acc);
    void SetPlayerState(PLAYER_STATE _state) { m_curState = _state; }
    void SetAnimOffsetPos(bool shellOn);
    void SetColliderOffsetPos();
    void SetTryText() 
    {
        std::stringstream ss;
        ss << std::to_string(_tryCnt) << "'st";
        std::string str = ss.str();
        _tryText.clear();
        _tryText.assign(str.begin(), str.end());
    }
    void SetTryTextHide()
    {
        _tryText = L"";
    }

private:
    void Jump();
    void DoubleJump();
    //bool CheckGroundCollider();
    void Land();
    void CreateInit();
    void SetShellOff();
    void InitJump() { _jumpPower = -550.f; }
    void ReStart();
    const int& GetTryCnt() { return _tryCnt; }
private:
    float _isCreateEnd;
    float _jumpTime;
    float _curTime;
    float _detectTimer;
    bool _shellOn;
    bool _isCanDetect;
    bool _isJump;
    bool _isDoubleJump;
    float _jumpPower;
    float _acc;
    bool _isGround;
    float _dir;
    float _jumpLevel;
    float _width;
    float _height;
    int _tryCnt;
    wstring _tryText;
    float textTime;
    std::shared_ptr<Texture> m_pTex;
    std::shared_ptr<Texture> m_idleTex;
    PLAYER_STATE m_curState;
    PLAYER_COL_INFO m_colInfo;
};

