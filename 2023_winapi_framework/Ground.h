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
	virtual void EnterCollision(Collider* other) override;
	virtual void StayCollision(Collider* other) override;
	virtual void ExitCollision(Collider* other) override;
public:
	void CheckColDirPlayer(Object* otherObj);
	void CheckColDirShell(Object* otherObj);
private:
	bool _onGround;
	bool _isCollision;
	Player* m_player;
};

