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
	
	Vec2		m_Force; // ��
	Vec2			m_Accel; // ���ӵ�
	Vec2		m_accelAlpha; // ���ӵ�
					// V += at
	Vec2		m_Velocity; //�ӵ�

	Vec2		m_MaxVelocity; //�ִ� �ӵ�
					//������ = ������� * ��
	float		m_fMass; // ����
	float		m_fricCoef;
};