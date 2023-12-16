#include "pch.h"
#include "Game_Scene.h"
#include "Core.h"
#include "Object.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "ResMgr.h"
#include "MapObject.h"
#include "MapMgr.h"
#include "CameraMgr.h"
#include "ShellObject.h"
#include "Gravity.h"
#include "Background.h"

void Game_Scene::Init()
{
	MapMgr::GetInst()->CreateJsonBoard();
	Vec2 vResolution = Core::GetInst()->GetResolution();
	
	Background* m_bg = new Background;
	m_bg->SetPos(vResolution);
	ADDBG(m_bg);


	Object* m_Player = new Player;

	//AddObject(m_Player, OBJECT_GROUP::PLAYER);

	int size = MapMgr::GetInst()->GetMapObjs().size();
	for (int i = 0; i < MapMgr::GetInst()->GetMapObjs().size(); i++)
	{
		AddObject(MapMgr::GetInst()->GetMapObjs()[i], OBJECT_GROUP::GROUND);
	}

	for (int i = 0; i < MapMgr::GetInst()->GetShellObjs().size(); i++)
	{
		//AddObject(MapMgr::GetInst()->GetShellObjs()[i], OBJECT_GROUP::SHELL);
	}

	//ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->LoadSound(L"Jump", L"Sound\\Jump.wav", false);
	ResMgr::GetInst()->LoadSound(L"Land", L"Sound\\Land.wav", false);
	ResMgr::GetInst()->LoadSound(L"Bump", L"Sound\\Bump.wav", false);
	ResMgr::GetInst()->Play(L"BGM");

	//// 충돌체크해야되는것들을 설정하자
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::GROUND);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::SHELL);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::GROUND, OBJECT_GROUP::SHELL);
	CameraMgr::GetInst()->SetTarget(m_Player);
	CameraMgr::GetInst()->SetPrevLook(MapMgr::GetInst()->GetEndPoint());
	CameraMgr::GetInst()->SetLook(m_Player->GetPos());
}
