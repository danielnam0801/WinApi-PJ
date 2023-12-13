#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"
#include "TimeMgr.h"

Rigidbody::Rigidbody()
	: m_fMass(1.f)
	, m_Force(Vec2(0.f, 0.f))
	, m_Velocity(Vec2(0.f, 0.f))
	, m_fricCoef(250.f)
	, m_MaxVelocity(400.f, 1200.f)
{

}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::FinalUpdate(float _dt)
{
	// F = ma
	// a = F / m
	// v+= at
	float fForce = m_Force.Length();
	if (fForce != 0.f)
	{
		m_Force.Normalize();
		Vec2 accel = m_Force / m_fMass;
		m_Accel = m_Force * accel;
	}

	m_Accel += m_accelAlpha;
	m_Velocity += m_Accel * _dt;

	//마찰
	if (m_Velocity.x != 0.f)
	{
		Vec2 Friction = m_Velocity * -1;
		Friction.y = 0;
		Vec2 FrictionDir = Friction.Normalize();
		Friction = FrictionDir * m_fricCoef * _dt;

		if (m_Velocity.Length() <= Friction.Length())
		{
			m_Velocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_Velocity += Friction;
		}
	}

	// 최대 속도 제한
	if (abs(m_MaxVelocity.x) < abs(m_Velocity.x))
	{
		m_Velocity.x = (m_Velocity.x / abs(m_Velocity.x)) * m_MaxVelocity.x;
	}
	if (abs(m_MaxVelocity.y) < abs(m_Velocity.y))
	{
		m_Velocity.y = (m_Velocity.y / abs(m_Velocity.y)) * m_MaxVelocity.y;
	}

	Move(_dt);
	
	m_Force = Vec2(0.f, 0.f);
	m_accelAlpha = Vec2(0.f, 0.f);
	m_Accel = Vec2(0.f, 0.f);
}

void Rigidbody::Move(float _dt)
{
	float speed = m_Velocity.Length();
	if (0.f != speed)
	{
		Vec2 dir = m_Velocity;
		dir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();
		vPos += dir * speed * _dt;

		m_pOwner->SetPos(vPos);
	}
}

