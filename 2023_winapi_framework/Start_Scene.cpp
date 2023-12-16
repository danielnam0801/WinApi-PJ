#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "MapObject.h"
#include "Ground.h"
#include "MapMgr.h"
#include "Btn.h"
#include "SceneMgr.h"
#include "Vec2.h"
#include"Texture.h"
#include <functional>
#include "Background.h"
#include<io.h>
using namespace std;

Vec2 vec;

void Start_Scene::Init()
{
	std::shared_ptr<Texture> bgTex = ResMgr::GetInst()->TexLoad(L"SlimeBG", L"Texture\\Slime.bmp");
	Background* bg = new Background(bgTex);
	AddObject(bg, OBJECT_GROUP::UI);

	Btn* Btn1 = new Btn([]()
		{
			SceneMgr::GetInst()->LoadScene(SCENE_TYPE::GAME_SCENE);
		}
	, L"Game Start", L"ASDF", L"Texture\\Button1.bmp");
	Btn1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 4 * 2 - 70 })));

	Btn1->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn1, OBJECT_GROUP::UI);

	Btn* Btn2 = new Btn([]()
		{
			SceneMgr::GetInst()->LoadScene(SCENE_TYPE::EXPLAIN_SCENE);
		}
	, L"Game Info", L"ASDF", L"Texture\\Button1.bmp");
	Btn2->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	Btn2->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn2, OBJECT_GROUP::UI);

	Btn* Btn3 = new Btn([]()
		{
			SceneMgr::GetInst()->LoadScene(SCENE_TYPE::GAMEOVER_SCENE);
		}
	, L"Game Over", L"ASDF", L"Texture\\Button1.bmp");
	Btn3->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 6 * 4 - 110 })));
	Btn3->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn3, OBJECT_GROUP::UI);

}


void Start_Scene::Update()
{
	Scene::Update();
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}

