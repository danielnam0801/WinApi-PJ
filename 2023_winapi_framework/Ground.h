#pragma once
#include "Object.h"
class Player;
class Ground : public Object
{
public:
	Ground();
	~Ground();
public:
	const bool& IsGround() const { return _onGround; }
	const bool& IsCollision() const { return _isCollision; }
public:
	void Update() override;
	void Render(HDC _dc) override;
	void EnterCollision(Collider* other) override;
	void StayCollision(Collider* other) override;
private:
	bool _onGround;
	bool _isCollision;
	Player* m_player;
};

