#include "pch.h"
#include "Ground.h"
#include "Collider.h"
#include "Gravity.h"
#include "Player.h"
#include "ShellObject.h"

Ground::Ground()
{
	CreateCollider();
}

Ground::~Ground()
{
	
}

void Ground::Update()
{	
}

void Ground::Render(HDC _dc)
{
	//Component_Render(_dc);
}

void Ground::EnterCollision(Collider* other)
{
	Object* otherObj = other->GetObj();
	if (otherObj->GetName() == L"Player")
	{
		Player* player = dynamic_cast<Player*>(otherObj);
		PLAYER_STATE playerCurState = player->GetCurState();

		if (playerCurState == PLAYER_STATE::MOVE || playerCurState == PLAYER_STATE::IDLE)
		{
			return;
		}

		if (playerCurState == PLAYER_STATE::JUMP || playerCurState == PLAYER_STATE::FALL)
		{
			CheckColDirPlayer(otherObj);
		}
	}
	if (otherObj->GetName() == L"Shell")
	{
		CheckColDirShell(otherObj);
	}
}

void Ground::StayCollision(Collider* other)
{
	Object* otherObj = other->GetObj();

	if (otherObj->GetName() == L"Player")
	{
		CheckColDirPlayer(otherObj);
	}
	if (otherObj->GetName() == L"Shell")
	{
		CheckColDirShell(otherObj);
	}
}

void Ground::ExitCollision(Collider* other)
{

}

void Ground::CheckColDirPlayer(Object* otherObj)
{
	Player* player = dynamic_cast<Player*>(otherObj);
	PLAYER_STATE playerCurState = player->GetCurState();

	Vec2 playerPos = otherObj->GetCollider()->GetFinalPos();
	Vec2 playerScale = otherObj->GetCollider()->GetScale();

	Vec2 groundPos = GetCollider()->GetFinalPos();
	Vec2 groundScale = GetCollider()->GetScale();

	float playerRightPosX = playerPos.x + (playerScale.x / 2.f);
	float playerLeftPosX = playerPos.x - (playerScale.x / 2.f);
	float playerTopPosY = playerPos.y - (playerScale.y / 2.f);
	float playerBottomPosY = playerPos.y + (playerScale.y / 2.f);

	float groundRightPosX = groundPos.x + (groundScale.x / 2.f);
	float groundLeftPosX = groundPos.x - (groundScale.x / 2.f);
	float groundTopPosY = groundPos.y - (groundScale.y / 2.f);
	float groundBottomPosY = groundPos.y + (groundScale.y / 2.f);

	// ground À§ÂÊ¸é ºÎµúÈú °æ¿ì(ÇÃ·¹ÀÌ¾î°¡ ¶¥À§¿¡ ¼­ ÀÖÀ» °æ¿ì
	if (playerBottomPosY >= groundTopPosY && playerTopPosY < groundPos.y)
	{
		if (playerRightPosX <= (groundRightPosX + playerScale.x / 2.f) && playerLeftPosX >= groundLeftPosX - (playerScale.x / 2.f))
		{
			// ³ª(¶¥ ±âÁØ)ÀÇ ³ªÀÇ(¶¥ÀÇ) ¾Æ·§¸é¿¡ Ãæµ¹ÇßÀ» ¶§
			PLAYER_COL_INFO info = { false, false, false, true };
			player->SetPlayerColInfo(info);

			otherObj->GetGravity()->SetOnGround(true);

			float lenY = abs(playerPos.y - groundPos.y);
			float valueY = ((playerScale.y / 2.f) + (groundScale.y / 2.f)) - lenY;
			playerPos = otherObj->GetPos();
			playerPos.y -= valueY;

			otherObj->SetPos(playerPos);
			player->SetPlayerState(PLAYER_STATE::IDLE);
			return;
		}
	}

	// ground ¿ÞÂÊ¸é ºÎµúÈú °æ¿ì
	if (playerRightPosX >= groundLeftPosX && playerPos.x < groundLeftPosX)
	{
		if (groundTopPosY - (playerScale.y / 2.f) < playerTopPosY && groundBottomPosY + (playerScale.y / 2.f) > playerBottomPosY)
		{
			PLAYER_COL_INFO info = { true, false, false, false };
			player->SetPlayerColInfo(info);

			float lenX = abs(playerPos.x - groundPos.x);
			float valueX = ((playerScale.x / 2.f) + (groundScale.x / 2.f)) - lenX;
			playerPos = otherObj->GetPos();
			playerPos.x -= valueX;

			otherObj->SetPos(playerPos);
			return;
		}
	}

	// ground ¿À¸¥ÂÊ¸é ºÎµúÈú °æ¿ì
	if (playerLeftPosX <= groundRightPosX && playerPos.x > groundRightPosX)
	{
		if (groundTopPosY - (playerScale.y / 2.f) < playerTopPosY && groundBottomPosY + (playerScale.y / 2.f) > playerBottomPosY)
		{
			PLAYER_COL_INFO info = { false, true, false, false };
			player->SetPlayerColInfo(info);

			float lenX = abs(playerPos.x - groundPos.x);
			float valueX = ((playerScale.x / 2.f) + (groundScale.x / 2.f)) - lenX;
			playerPos = otherObj->GetPos();
			playerPos.x += valueX;

			otherObj->SetPos(playerPos);
			return;
		}
	}

	// ground ¾Æ·§¸é ºÎµúÈú °æ¿ì
	if (playerTopPosY - 5 < groundBottomPosY && playerPos.y > groundBottomPosY)
	{
		if (playerRightPosX <= (groundRightPosX + playerScale.x / 2.f) && playerLeftPosX >= groundLeftPosX - (playerScale.x / 2.f))
		{
			PLAYER_COL_INFO info = { false, false, true, false };
			player->SetPlayerColInfo(info);

			float lenY = abs(playerPos.y - groundPos.y);
			float valueY = ((playerScale.y / 2.f) + (groundScale.y / 2.f)) - lenY;
			playerPos = otherObj->GetPos();
			playerPos.y += valueY;

			otherObj->SetPos(playerPos);

			return;
		}
	}
}

void Ground::CheckColDirShell(Object* otherObj)
{
	ShellObject* shell = reinterpret_cast<ShellObject*>(otherObj);

	Vec2 shellPos = shell->GetCollider()->GetFinalPos();
	Vec2 shellScale = shell->GetCollider()->GetScale();

	Vec2 groundPos = GetCollider()->GetFinalPos();
	Vec2 groundScale = GetCollider()->GetScale();

	float shellBottomPosY = shellPos.y + (shellScale.y / 2.f);
	float groundTopPosY = groundPos.y - (groundScale.y / 2.f);

	if (shellBottomPosY >= groundTopPosY)
	{
		otherObj->GetGravity()->SetOnGround(true);

		float lenY = abs(shellPos.y - groundPos.y);
		float valueY = ((shellScale.y / 2.f) + (groundScale.y / 2.f)) - lenY;
		shellPos = otherObj->GetPos();
		shellPos.y -= valueY;

		otherObj->SetPos(shellPos);
	}
}
