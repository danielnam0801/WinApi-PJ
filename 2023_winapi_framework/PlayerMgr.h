#pragma once
class Player;
class PlayerMgr
{
	SINGLE(PlayerMgr);
public:
	void Init();
	void Update();
	void Render(HDC _dc);
public:
	Player* GetPlayer() { return m_Player; }
private:
	Player* m_Player;
};

