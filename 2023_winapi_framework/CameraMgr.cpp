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

    // ȭ�� �߾���ǥ�� ī�޶� Lookat ��ǥ���� ���̰� ���
    CalDiff();
}

void CameraMgr::CalDiff()
{  
    //// ���� LookAt�� ���� LookAt�� ���̰��� �����ؼ� ���� LookaT�� ���Ѵ�.
    //m_vLootAt; // ���� ���� �ִ� ��ġ
    //m_vPrevLookAt; // ���� ��ġ
    //// �̰� �����ؾ��Ѵ�.. �̰� ���� �ð��� ���� �Ѿư��� �غ���.

    // �ð��� ���� �̵�
    m_fAccTime += fDT;
    if (m_fAccTime >= m_fTime)
    {
        m_vCurLookAt = m_vLootAt; // �ð��Ǹ� �̷��� ����Look�� ����
    }
    else
    {
        Vec2 vLookDir = m_vLootAt - m_vPrevLookAt; // �Ѿư� ���� ����
        m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;

    }
    //// �׳� �Ѿư���
    //Vec2 vLookDir = m_vLootAt - m_vPrevLookAt; // �Ѿư� ���� ����
    //m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * 500.f * fDT;

    Vec2 vResolution = Core::GetInst()->GetResolution();
    Vec2 vCenterPos = vResolution / 2.f;

    // ���� �ִ� ��ġ�� �߽���ġ�� ���� ��.
    //m_vDiff = m_vLootAt - vCenterPos;
    m_vDiff = m_vCurLookAt - vCenterPos;
    std::cout << m_vDiff.x << m_vDiff.y;
    //m_vPrevLookAt = m_vLootAt;
    m_vPrevLookAt = m_vCurLookAt;
}