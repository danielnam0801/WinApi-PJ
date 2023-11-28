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
	void AddForce(Vec2 _force) { m_Force += _force; };
	void SetVelocity(Vec2 _v){  m_Velocity = _v; }
	void AddVelocity(Vec2 _v) { m_Velocity += _v; }
	void SetMaxSpeed(float speed) { m_MaxSpeed = speed; }
	void SetFricCoef(float fricCoef) { m_fricCoef = fricCoef; }
	void SetGravity(float gravity) { m_gravity = gravity; }
	void SetApplyGravity(bool value) { m_useGravity = value; }
	void StopImmediately() { m_Velocity = { 0.0f, 0.0f }; }
private:
	Object* m_pOwner;
	friend class Object;
	Vec2 m_Force; // ��
	float	 m_fMass; // ����
	Vec2 m_Accel; // ���ӵ�
					// V += at
	Vec2 m_Velocity; //�ӵ�

	float	 m_MaxSpeed; //�ִ� �ӵ�
					//������ = ������� * ��
	float	 m_fricCoef;
	float	 m_gravity;
	bool	 m_useGravity;
};