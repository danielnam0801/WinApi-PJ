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
}

MapObject::~MapObject()
{
}

void MapObject::DeepCopy(MapObject* rhs)
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
	Vec2 vPos = GetPos();
	vPos = CameraMgr::GetInst()->GetLocalPos(vPos);
	
	int Width = m_texRect.right;
	int Height = m_texRect.bottom;
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, Width, Height, m_tex->GetDC()
		, m_texRect.left, m_texRect.top, Width, Height, RGB(255, 255, 255));

	StretchBlt(_dc
		, (int)(vPos.x - m_vScale.x / 2)
		, (int)(vPos.y - m_vScale.y / 2)
		, Width * m_vScale.x, Height * m_vScale.y, m_tex->GetDC()
		, 0, 0, Width, Height, SRCCOPY);
	//RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	//Component_Render(_dc);
}
