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

ShellObject::ShellObject()
{
	CreateCollider();
	m_vScale = Vec2{ 1.5f,1.5f };
	SetName(L"Shell");
	m_tex = ResMgr::GetInst()->TexLoad(L"Shell", L"Texture\\Shell.bmp");
	GetCollider()->SetScale(Vec2{40,30});
	int Width = m_tex->GetWidth() / 2 * m_vScale.x;
	int Height = m_tex->GetHeight() / 2;
	GetCollider()->SetOffSetPos(Vec2{ Width , Height });
	CreateRigidbody();
	//CreateGravity();
}

ShellObject::~ShellObject()
{

}

void ShellObject::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos = CameraMgr::GetInst()->GetLocalPos(vPos);

	int Width = m_tex->GetWidth();
	int Height = m_tex->GetHeight();

	// 2. ���� �Ⱦ��
	TransparentBlt(_dc
		, (int)(vPos.x - m_vScale.x / 2)
		, (int)(vPos.y - m_vScale.y / 2)
		, Width, Height, m_tex->GetDC()
		, 0, 0, Width,Height, RGB(255,255,255));

	StretchBlt(_dc
		, (int)(vPos.x - m_vScale.x / 2)
		, (int)(vPos.y - m_vScale.y / 2)
		, Width * m_vScale.x, Height * m_vScale.y, m_tex->GetDC()
		, 0, 0, Width, Height, SRCCOPY);
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}

void ShellObject::EnterCollision(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		Player* pPlayer = reinterpret_cast<Player*>(_pOther->GetObj());
		if (!pPlayer->GetShell())
		{
			pPlayer->SetShell();
			m_IsAlive = false;
		}
	}
}