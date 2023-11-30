#pragma once
class Object;
class Rigidbody
{
public:
	Rigidbody();
	~Rigidbody();
public:
	void FinalUpdate(float _dt);
	void Move(float _dt);
	void AddForce(Vec2 _force)
	{
		m_Force += _force;
	}
	void SetAccelAlpha(Vec2 _force)
	{
		m_accelAlpha += _force;
	}
	void SetVelocity(Vec2 _v)
	{
		m_Velocity = _v;
	}
	void AddVelocity(Vec2 _v)
	{
		m_Velocity += _v;
	}
	void SetMaxVelocity(Vec2 _v)
	{
		m_MaxVelocity = _v;
	}
	const Vec2& const GetVelocity()
	{
		return m_Velocity;
	}
	void SetFricCoef(float fricCoef) { m_fricCoef = fricCoef; }
	void StopImmediately() { m_Velocity = { 0.0f, 0.0f }; }
private:
	Object* m_pOwner;
	friend class Object;
	
	Vec2		m_Force; // 힘
	Vec2			m_Accel; // 가속도
	Vec2		m_accelAlpha; // 가속도
					// V += at
	Vec2		m_Velocity; //속도

	Vec2		m_MaxVelocity; //최대 속도
					//마찰력 = 마찰계수 * 힘
	float		m_fMass; // 질량
	float		m_fricCoef;
};