#include "pch.h"
#include "Gravity.h"
#include "Object.h"
#include "Rigidbody.h"
#include "TimeMgr.h"

Gravity::Gravity()
	: m_useGravity(true)
	, m_gravity(1400.f)
	, m_onGround(false)
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

void Gravity::SetOnGround(bool value)
{
	m_onGround = value;
	if (m_onGround)
	{
		m_pOwner->GetRigidbody()->SetVelocity(Vec2(0.f, 0.f));
	}
}
