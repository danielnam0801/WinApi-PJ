#include "pch.h"
#include "ShellObject.h"
#include "Collider.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Gravity.h"
#include "CameraMgr.h"
#include "Object.h"
#include "Player.h"
#include "SceneMgr.h"

ShellObject::ShellObject()
{
	CreateCollider();
	CreateRigidbody();
	CreateGravity();
	m_vScale = Vec2{ 1.5f,1.5f };
	SetName(L"Shell");
	m_tex = ResMgr::GetInst()->TexLoad(L"Shell", L"Texture\\Shell.bmp");
	GetCollider()->SetScale(Vec2{30,30});
	int Width = m_tex->GetWidth() / 2 * m_vScale.x;
	int Height = m_tex->GetHeight() / 2;
	GetCollider()->SetOffSetPos(Vec2{ Width , Height });
	GetGravity()->SetGravity(100.f);
	GetGravity()->SetApplyGravity(false);
	enabled = true;
}

ShellObject::~ShellObject()
{

}

void ShellObject::Update()
{
	if (m_vPos.y > 5000.f)
	{
		Reload();
	}
}

void ShellObject::Render(HDC _dc)
{
	if (enabled == false) return;
	Vec2 vPos = GetPos(); 
	vPos = CameraMgr::GetInst()->GetLocalPos(vPos);

	int Width = m_tex->GetWidth();
	int Height = m_tex->GetHeight();
	
	TransparentBlt(_dc
		, (int)(vPos.x - m_vScale.x / 2)
		, (int)(vPos.y - m_vScale.y / 2)
		, Width * 1.6, Height * 1.6, m_tex->GetDC()
		, 0, 0, Width, Height, RGB(255, 255, 255));

	Component_Render(_dc);
}

void ShellObject::EnterCollision(Collider* _pOther)
{
	if (enabled == false) return;
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		Player* pPlayer = reinterpret_cast<Player*>(_pOther->GetObj());
		if (!pPlayer->GetShell() && pPlayer->IsCanDetect())
		{
			pPlayer->SetShell();
			enabled = false;
		}
	}

	if (_pOther->GetObj()->GetName() == L"Ground")
	{
		GetGravity()->SetApplyGravity(false);
	}
}

void ShellObject::Reload()
{
	m_vPos = spawnPoint;
	enabled = true;
}

