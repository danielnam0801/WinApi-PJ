#include "pch.h"
#include "MapObject.h"
#include "Collider.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"

MapObject::MapObject()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2((float)m_texRect.right, (float)m_texRect.bottom));
	//GetCollider()->SetScale(Vec2(1000.f, 100.f));
	//SetTexture(ResMgr::GetInst()->TexLoad(L"MapTex1", L"Texture\\demo-tileset.bmp"));
}

MapObject::~MapObject()
{
}

void MapObject::Render(HDC _dc)
{
	GetCollider()->SetScale(Vec2((float)m_texRect.right, (float)m_texRect.bottom));
	int Width = m_texRect.right;
	int Height = m_texRect.bottom;
	TransparentBlt(_dc
		, (int)(m_vPos.x)
		, (int)(m_vPos.y)
		, Width, Height, m_tex->GetDC()
		, m_texRect.left, m_texRect.top, Width, Height, RGB(255, 255, 255));

	//RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}
