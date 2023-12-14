#include "pch.h"
#include "Gravity.h"
#include "Object.h"
#include "Rigidbody.h"
#include "TimeMgr.h"

Gravity::Gravity()
	: m_useGravity(true)
	, m_gravity(1400.f)
{

}

Gravity::~Gravity()
{
}

void Gravity::FinalUpdate()
{
	if (!m_useGravity) return;
	m_pOwner->GetRigidbody()->SetAccelAlpha(Vec2(0.f, m_gravity));
	//Vec2 vPos = m_pOwner->GetPos();
	
}
