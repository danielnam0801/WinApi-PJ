#pragma once
class Object;
class Gravity
{
public:
	Gravity();
	~Gravity();
public:
	void FinalUpdate();
	void SetGravity(float gravity) { m_gravity = gravity; }
	void SetApplyGravity(bool value) { m_useGravity = value; }
private:
	float	 m_gravity;
	bool	 m_useGravity;
	Object*  m_pOwner;
	friend class Object;
};

