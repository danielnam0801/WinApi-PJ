#pragma once
class Player;
class PlayerMgr
{
	SINGLE(PlayerMgr)
	public:
		void SetPlayer(Player* other) { m_Player = other; }
		Player* GetPlayer() { return m_Player; }
	private:
		Player* m_Player;
};

