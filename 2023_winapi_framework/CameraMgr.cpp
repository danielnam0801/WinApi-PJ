#include "pch.h"
#include "Camera.h"
#include "CameraMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Core.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
void CameraMgr::Init()
{
	//if (_mainCam == nullptr)
	//	_mainCam = new Camera();
	//	SceneMgr::GetInst()->GetCurScene()->AddObject(_mainCam, OBJECT_GROUP::CAMERA);	
}

void CameraMgr::Update()
{
	if (m_pObj != nullptr)
	{
		//죽었어 // 추가로 예외처리
		m_vLook = m_pObj->GetPos();
	}
	if (KEY_PRESS(KEY_TYPE::A))
		m_vLook.x -= 800.f * fDT;
	if (KEY_PRESS(KEY_TYPE::D))
		m_vLook.x += 800.f * fDT;

	Vec2 vResolution = Core::GetInst()->GetResolution();
	Vec2 vCenter = Vec2(vResolution.x / 2, vResolution.y / 2);
	m_vDiff = m_vLook - vCenter;
}

void CameraMgr::Render(HDC _dc)
{
}
