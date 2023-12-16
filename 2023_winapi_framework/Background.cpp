#include "pch.h"
#include "Background.h"
#include "ResMgr.h"
#include "Texture.h"
#include "CameraMgr.h"

Background::Background(std::shared_ptr<Texture> tex)
{
	SetScale(Vec2{ 3.f, 3.f });
	m_tex = tex;

}

Background::~Background()
{
}

void Background::Render(HDC _dc)
{
	int Width = m_tex->GetWidth();
	int Height = m_tex->GetHeight();
	StretchBlt(_dc
		, (int)(m_vPos.x - m_vScale.x / 2)
		, (int)(m_vPos.y - m_vScale.y / 2)
		, Width * m_vScale.x, Height * m_vScale.y, m_tex->GetDC()
		, 0, 0, Width, Height, SRCCOPY);
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}
