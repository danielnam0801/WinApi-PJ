#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"
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
#include<io.h>
using namespace std;

Vec2 vec;

void Start_Scene::Init()
{
	ResMgr::GetInst()->TexLoad(L"Slime.bmp", L"Texture\\Slime.bmp");

	Btn* Btn1 = new Btn([]()
	{
		SceneMgr::GetInst()->LoadScene(SCENE_TYPE::GAME_SCENE);
	}
	, L"���� ����");
	Btn1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 4 * 2 - 70 })));
	Btn1->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn1, OBJECT_GROUP::UI);

	Btn* Btn2 = new Btn([]()
		{
			SceneMgr::GetInst()->LoadScene(SCENE_TYPE::EXPLAIN_SCENE);
		}
	, L"���� ����",L"ASDF",L"Texture\\Button1.bmp");
	Btn2->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	Btn2->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn2, OBJECT_GROUP::UI);

	Btn* Btn3 = new Btn([]()
		{
			SceneMgr::GetInst()->LoadScene(SCENE_TYPE::GAMEOVER_SCENE);
		}
	, L"���� ����",L"ASDF",L"Texture\\Button1.bmp");
	Btn3->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y /6*4-110})));
	Btn3->SetScale(Vec2(100.f, 30.f));
	AddObject(Btn3, OBJECT_GROUP::UI);

	// ���� ���� �������� ��ġ�� �غ��ô�.

	//Monster* pMonster = nullptr;
	//int iMonster = 10;		// ���� �� 
	//float fMoveDist = 30.f; // ������ �Ÿ�
	//float fMonsterScale = 50.f; // ���� ũ��
	//// �ػ�x - ( ������ �Ÿ� + ������Ʈ ũ�� /2) * 2 / ���ͼ� -1 
	//float fTerm = (vResolution.x - (fMoveDist + fMonsterScale / 2.f) * 2) 
	//				/ (float)(iMonster -1);
	//for (int i = 0; i < iMonster; ++i)
	//{
	//	pMonster = new Monster;
	//	pMonster->SetPos(Vec2(
	//		(fMoveDist + fMonsterScale / 2.f) + i* fTerm
	//		,300.f));
	//	pMonster->SetScale(Vec2(fMonsterScale, fMonsterScale));
	//	pMonster->SetCenterPos(pMonster->GetPos());
	//	pMonster->SetMoveDis(fMoveDist);
	//	AddObject(pMonster, OBJECT_GROUP::MONSTER);
	//}
	// ���� ����

	// �浹üũ�ؾߵǴ°͵��� ��������.
	/*CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::MOUSE, OBJECT_GROUP::MAP);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::GROUND);*/
}


void Start_Scene::Update()
{
	Scene::Update();
	//if(KEY_DOWN(KEY_TYPE::ENTER))
	//	// �� ����
}

void Start_Scene::Render(HDC _dc)
{
	
	Scene::Render(_dc);
	shared_ptr<Texture> backgroundTexture = ResMgr::GetInst()->TexFind(L"Slime.bmp");
	if (backgroundTexture)
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();

		int Width = backgroundTexture->GetWidth();
		int Height = backgroundTexture->GetHeight();

		StretchBlt(_dc, 0, 0, (int)vScale.x, (int)vScale.y, backgroundTexture->GetDC(), 0, 0, Width, Height, SRCCOPY);
	}


	//Vec2 vPos = Vec2(Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y);

	//shared_ptr<Texture> texture = ResMgr::GetInst()->TexFind(L"asdf");

	//if (texture)
	//{
	//	int Width = texture->GetWidth();
	//	int Height = texture->GetHeight();
	//}
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}

