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
	void SetOnGround(bool value);
	const bool& GetGround() { return m_onGround; }
private:
	float	 m_gravity;
	bool	 m_useGravity;
	bool	 m_onGround;
	Object*  m_pOwner;
	friend class Object;
};

