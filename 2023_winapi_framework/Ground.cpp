#include "pch.h"
#include "Ground.h"
#include "Collider.h"
#include "Gravity.h"
#include "Player.h"

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

		// =============================================
		// JUMP �ƴ� ��� �浹üũ
		// =============================================
		if (playerCurState == PLAYER_STATE::MOVE || playerCurState == PLAYER_STATE::IDLE)
		{
			return;
		}

		// =============================================
		// JUMP�� ��� �浹üũ
		// =============================================
		if (playerCurState == PLAYER_STATE::JUMP || playerCurState == PLAYER_STATE::FALL)
		{
			CheckColDir(otherObj);
		}
	}
}

void Ground::StayCollision(Collider* other)
{
	Object* otherObj = other->GetObj();

	if (otherObj->GetName() == L"Player")
	{
		CheckColDir(otherObj);
	}
}

void Ground::ExitCollision(Collider* other)
{

}

void Ground::CheckColDir(Object* otherObj)
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

	// ground ���ʸ� �ε��� ���(�÷��̾ ������ �� ���� ���
	if (playerBottomPosY >= groundTopPosY && playerTopPosY < groundPos.y)
	{
		if (playerRightPosX <= (groundRightPosX + playerScale.x / 2.f) && playerLeftPosX >= groundLeftPosX - (playerScale.x / 2.f))
		{
			// ��(�� ����)�� ����(����) �Ʒ��鿡 �浹���� ��
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

	// ground ���ʸ� �ε��� ���
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

	// ground �����ʸ� �ε��� ���
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

	// ground �Ʒ��� �ε��� ���
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