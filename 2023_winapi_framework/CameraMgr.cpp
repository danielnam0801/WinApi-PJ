#include "pch.h"
#include "Camera.h"
#include "CameraMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

void CameraMgr::Init()
{
	if (_mainCam == nullptr)
		_mainCam = new Camera();
	SceneMgr::GetInst()->GetCurScene()->AddObject(_mainCam, OBJECT_GROUP::CAMERA);
}

void CameraMgr::Update()
{
}

void CameraMgr::Render(HDC _dc)
{
}
