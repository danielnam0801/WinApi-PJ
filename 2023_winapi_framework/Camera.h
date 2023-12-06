#pragma once
#include "Object.h"
class Camera : public Object
{
public:
	Camera();
public:
	void Update();
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void ExitCollision(Collider* _pOther) override;
	virtual void StayCollision(Collider* _pOther) override;
private:	
	void CameraMove();
private:
	Vec2 m_targetPoint;
	Vec2 m_lerpSpeed;
};

