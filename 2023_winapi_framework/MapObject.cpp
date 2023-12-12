#include "pch.h"
#include "MapObject.h"
#include "Collider.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "CameraMgr.h"

MapObject::MapObject()
{
	CreateCollider();
	//GetCollider()->SetScale(Vec2(1000.f, 100.f));
	//SetTexture(ResMgr::GetInst()->TexLoad(L"MapTex1", L"Texture\\demo-tileset.bmp"));
	//GetCollider()->SetScale(Vec2((float)m_texRect.right, (float)m_texRect.bottom));
}

MapObject::~MapObject()
{
}

//MapObject::MapObject(const MapObject& rhs)
//{
//	this->m_texRect = rhs.m_texRect;
//
//	// 텍스처를 깊은 복사
//	if (rhs.m_tex) {
//		this->m_tex = std::make_shared<Texture>(*rhs.m_tex);
//	}
//	else {
//		this->m_tex = nullptr;
//	}
//
//	this->m_vPos = rhs.m_vPos;
//	this->m_vScale = rhs.m_vScale;
//	this->m_strName = rhs.m_strName;
//	this->m_IsAlive = rhs.m_IsAlive;
//	this->m_IsClicked = rhs.m_IsClicked;
//
//}

void MapObject::DeepCopy(const std::shared_ptr<MapObject>& rhs)
{
	this->m_texRect = rhs->m_texRect;
	
		// 텍스처를 깊은 복사
	if (rhs->m_tex) {
		this->m_tex = std::make_shared<Texture>(*rhs->m_tex);
	}
	else {
		this->m_tex = nullptr;
	}
	
	this->m_strName = rhs->m_strName;
	
}

void MapObject::Render(HDC _dc)
{
	GetCollider()->SetScale(Vec2((float)m_texRect.right, (float)m_texRect.bottom));

	Vec2 vPos = GetPos();
	vPos = CameraMgr::GetInst()->GetLocalPos(vPos);
	
	int Width = m_texRect.right;
	int Height = m_texRect.bottom;
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, Width, Height, m_tex->GetDC()
		, m_texRect.left, m_texRect.top, Width, Height, RGB(255, 255, 255));

	//RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}
