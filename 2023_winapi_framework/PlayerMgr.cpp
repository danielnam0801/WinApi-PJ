#include "pch.h"
#include "PlayerMgr.h"
#include "Player.h"

void PlayerMgr::Init()
{
	if (m_Player != nullptr)
		delete m_Player;
	m_Player = new Player;
}

void PlayerMgr::Update()
{
}

void PlayerMgr::Render(HDC _dc)
{
}
