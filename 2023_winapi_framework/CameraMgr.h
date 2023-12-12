#pragma once
class Camera;
class CameraMgr
{
	SINGLE(CameraMgr);
private:
    float m_fTime = 2.f; // 타겟 따라가는데 걸리는 시간
    float m_fSpeed = 0.f; // 타겟 따라가는 속도
    float m_fAccTime = 0.f; // 누적시간
public:
    void SetLook(Vec2 _vLoot)
    {
        m_vLootAt = _vLoot;
        float fMoveDist = (m_vLootAt - m_vPrevLookAt).Length();
        m_fSpeed = fMoveDist / m_fTime; // 이동속도
        m_fAccTime = 0.f;
    }
    void SetTarget(Object* _pTargetObj)
    {
        m_pTargetObj = _pTargetObj;
    }
    const Vec2& GetLocalPos(Vec2 _vObjpos) const
    {
        return _vObjpos - m_vDiff;
    }
    const Vec2& GetRealPos(Vec2 _vRenderpos) const
    {
        return _vRenderpos + m_vDiff;
    }
public:
    void Update();
private:
    Vec2 m_vLootAt; // 카메라가 보는 위치
    Vec2 m_vPrevLookAt; // 카메라가 보는 이전 프레임 위치
    Vec2 m_vCurLookAt; // Look과 PrevLook 사이 어딜 봐야하는지
    // 보정해주는 실제 사용 LookAt

    Object* m_pTargetObj; // 카메라 타겟 오브젝트
    Vec2 m_vDiff; // 해상도 중심위치와 카메라 Lootat간의 차이값
private:
    void CalDiff(); // 차이 계산
};