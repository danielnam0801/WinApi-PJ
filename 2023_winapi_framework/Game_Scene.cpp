#include "pch.h"
#include "Game_Scene.h"
#include "Core.h"

#include "Object.h"
#include "Player.h"
#include "ShellObject.h"
#include "Background.h"
#include "MapObject.h"

#include "ResMgr.h"
#include "MapMgr.h"
#include "CameraMgr.h"
#include "CollisionMgr.h"
#include "PlayerMgr.h"
#include "SceneMgr.h"

void Game_Scene::Init()
{
	SetBkColor(Core::GetInst()->GetMainDC(), RGB(0, 0, 0));
	MapMgr::GetInst()->CreateJsonBoard();
	Vec2 vResolution = Core::GetInst()->GetResolution();
	
	std::shared_ptr<Texture> bgTex = ResMgr::GetInst()->TexLoad(L"GameBG", L"Texture\\Background.bmp");
	Background* m_bg = new Background(bgTex);
	m_bg->SetPos(vResolution);
	AddObject(m_bg, OBJECT_GROUP::UI);


	Player* m_Player = new Player;
	PlayerMgr::GetInst()->SetPlayer(m_Player);

	for (int i = 0; i < MapMgr::GetInst()->GetShellObjs().size(); i++)
	{
		AddObject(MapMgr::GetInst()->GetShellObjs()[i], OBJECT_GROUP::SHELL);
	}

	int size = MapMgr::GetInst()->GetMapObjs().size();
	for (int i = 0; i < MapMgr::GetInst()->GetMapObjs().size(); i++)
	{
		AddObject(MapMgr::GetInst()->GetMapObjs()[i], OBJECT_GROUP::GROUND);
	}

	AddObject(m_Player, OBJECT_GROUP::PLAYER);

	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->LoadSound(L"Jump", L"Sound\\Jump.wav", false);
	ResMgr::GetInst()->LoadSound(L"Land", L"Sound\\Land.wav", false);
	ResMgr::GetInst()->LoadSound(L"Bump", L"Sound\\Bump.wav", false);
	ResMgr::GetInst()->Play(L"BGM");

	//// 충돌체크해야되는것들을 설정하자
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::GROUND);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::SHELL);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::REMAKESHELL);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::SHELL, OBJECT_GROUP::GROUND);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::REMAKESHELL, OBJECT_GROUP::GROUND);
	CameraMgr::GetInst()->SetTarget(m_Player);
	CameraMgr::GetInst()->SetPrevLook(MapMgr::GetInst()->GetEndPoint());
	CameraMgr::GetInst()->SetLook(m_Player->GetPos());
}

void Game_Scene::Restart()
{
	std::vector<ShellObject*> shells = MapMgr::GetInst()->GetShellObjs();
	// 기본 배치된 껍데기들은 다시 활성화시켜준다.
	for (int i = 0; i < shells.size(); i++)
	{
		shells[i]->Reload();
	}

	// 새로 생성했던 껍데기들은 비워준다.
	std::vector<Object*> newShells = SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::REMAKESHELL);
	for (int i = 0; i < newShells.size(); i++)
	{
		newShells[i]->SetIsDead(true);
	}
}
