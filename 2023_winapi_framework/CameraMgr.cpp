#include "pch.h"
#include "Camera.h"
#include "CameraMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Core.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include <iostream>

void CameraMgr::Update()
{
    if (m_pTargetObj)
    {
        if (m_pTargetObj->GetIsDead())
        {
            m_pTargetObj = nullptr;
        }
        else
        {
            m_vLootAt = m_pTargetObj->GetPos();
        }
    }
    if (KEY_PRESS(KEY_TYPE::W))
        m_vLootAt.y -= 500.f * fDT;
    if (KEY_PRESS(KEY_TYPE::S))
        m_vLootAt.y += 500.f * fDT;
    if (KEY_PRESS(KEY_TYPE::A))
        m_vLootAt.x -= 500.f * fDT;
    if (KEY_PRESS(KEY_TYPE::D))
        m_vLootAt.x += 500.f * fDT;

    // 화면 중앙좌표와 카메라 Lookat 좌표간의 차이값 계산
    CalDiff();
}

void CameraMgr::CalDiff()
{  
    //// 이전 LookAt과 현재 LookAt의 차이값을 보정해서 현재 LookaT을 구한다.
    //m_vLootAt; // 지금 보고 있는 위치
    //m_vPrevLookAt; // 이전 위치
    //// 이걸 보정해야한다.. 이걸 일정 시간에 따라서 쫓아가게 해보자.

    // 시간에 따라 이동
    m_fAccTime += fDT;
    if (m_fAccTime >= m_fTime)
    {
        m_vCurLookAt = m_vLootAt; // 시간되면 이렇게 현재Look을 세팅
    }
    else
    {
        Vec2 vLookDir = m_vLootAt - m_vPrevLookAt; // 쫓아갈 방향 벡터
        m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;

    }
    //// 그냥 쫓아가게
    //Vec2 vLookDir = m_vLootAt - m_vPrevLookAt; // 쫓아갈 방향 벡터
    //m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * 500.f * fDT;

    Vec2 vResolution = Core::GetInst()->GetResolution();
    Vec2 vCenterPos = vResolution / 2.f;

    // 보고 있는 위치와 중심위치와 차이 값.
    //m_vDiff = m_vLootAt - vCenterPos;
    m_vDiff = m_vCurLookAt - vCenterPos;
    std::cout << m_vDiff.x << m_vDiff.y;
    //m_vPrevLookAt = m_vLootAt;
    m_vPrevLookAt = m_vCurLookAt;
}