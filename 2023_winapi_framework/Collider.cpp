#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"
#include "CameraMgr.h"

UINT Collider::m_sNextID = 0;
Collider::Collider()
	: m_pOwner(nullptr)
	, m_vScale(Vec2(40.f,40.f))
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
{
	//Collider a, b;
	//a = b;
}

Collider::Collider(const Collider& _origin)
	: m_pOwner(nullptr)
	, m_vScale(_origin.m_vScale)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
{
}

Collider::~Collider()
{}

void Collider::Render(HDC _dc)
{
	//Core::GetInst()->GetPen(PEN_TYPE::GREEN);
	//Core::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//SelectObject();
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_check)
		ePen = PEN_TYPE::RED;
	wstring name = GetObj()->GetName();
	SelectGDI pen(_dc, ePen);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);
	Vec2 vLocalPos = CameraMgr::GetInst()->GetLocalPos(m_vFinalPos);
	//RECT_RENDER(vLocalPos.x, vLocalPos.y, m_vScale.x, m_vScale.y, _dc);
}

void Collider::EnterCollision(Collider* _pOther)
{
 	++m_check;
	m_pOwner->EnterCollision(_pOther);
}

void Collider::ExitCollision(Collider* _pOther)
{
	--m_check;
	m_pOwner->ExitCollision(_pOther);
}

void Collider::StayCollision(Collider* _pOther)
{
	m_pOwner->StayCollision(_pOther);
}

bool Collider::OverlapSquare(Vec2 point, Vec2 size)
{

	return false;
}

void Collider::FinalUpdate()
{
	// Object위치를 따라가야 하는거야.
	wstring name = m_pOwner->GetName();
	Vec2 vObjPos = m_pOwner->GetPos();
	m_vFinalPos = vObjPos + m_vOffsetPos;
}

