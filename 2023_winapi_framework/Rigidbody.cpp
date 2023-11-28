#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"

Rigidbody::Rigidbody()
	: m_fMass(1.f)
	, m_Force(Vec2(0.f, 0.f))
	, m_Velocity(Vec2(0.f, 0.f))
	, m_fricCoef(0.1f)
	, m_MaxSpeed(10.f)
	, m_useGravity(false)
	, m_gravity(9.8f)
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
		if (m_useGravity) m_Accel.y += m_gravity;
		m_Accel = m_Force / m_fMass;
		m_Velocity += m_Accel * _dt;
	}


	//마찰
	if (m_Velocity.x != 0.f || m_Velocity.y != 0.f)
	{
		Vec2 Friction = m_Velocity * -1;
		Vec2 FrictionDir = Friction.Normalize();
		Friction = FrictionDir * m_fricCoef;

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
	float fVelocity = m_Velocity.Length();
	if (m_MaxSpeed < fVelocity)
	{
		m_Velocity.Normalize();
		m_Velocity = m_Velocity * m_MaxSpeed;
	}

	Move(_dt);
	m_Force = Vec2(0.f, 0.f);
}

void Rigidbody::Move(float _dt)
{
	Vec2 vPos = m_pOwner->GetPos();
	vPos += m_Velocity;
	m_pOwner->SetPos(vPos);
}