#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "Gravity.h"
#include "Ground.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "MapMgr.h"
#include <iostream>

Player::Player()
	: m_pTex(nullptr)
	, m_idleTex(nullptr)
	, _isJump(false)
	, _isDoubleJump(false)
	, m_curState(PLAYER_STATE::IDLE)
	, _jumpPower(-600.f)
	, _isGround(true)
	, _dir{ 0.0f }
	, _jumpTime{ 0.f }
	, _acc {0.f}
	, _curTime{ 0.f }
	, _isCreateEnd{ false }
	, _shellOn{ false }

{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\AllPlayer.bmp");
	CreateCollider();
	CreateRigidbody();
	CreateGravity();
	CreateAnimator();

	GetCollider()->SetScale(Vec2(20.f,30.f));
	//GetCollider()->SetOffSetPos(Vec2(0.f,-20.f));
	//GetAnimator()->CreateAnim(L"_Left", m_pTex,Vec2(0.f, 0.f),
	//	Vec2(25.f, 25.f), Vec2(25.f, 0.f), 13, 0.2f);
	//GetAnimator()->CreateAnim(L"_Right", m_pTex, Vec2(325.f, 0.f),
	//	Vec2(25.f, 25.f), Vec2(25.f, 0.f), 13, 0.2f);
	//GetAnimator()->CreateAnim(L"_Idle", m_pTex, Vec2(375.f, 0.f),
	//	Vec2(25.f, 25.f), Vec2(25.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Jump_Right", m_pTex,Vec2(0.f, 0.f),
		Vec2(70.f, 70.f), Vec2(70.f, 0.f), 13, 0.1f);
	GetAnimator()->CreateAnim(L"Jump_Left", m_pTex, Vec2(910.f, 0.f),
		Vec2(70.f, 70.f), Vec2(70.f, 0.f), 13, 0.1f);
	GetAnimator()->CreateAnim(L"_IdleLeft", m_pTex, Vec2(1050.f, 0.f),
		Vec2(70.f, 70.f), Vec2(70.f, 0.f), 1, 0.1f);	
	GetAnimator()->CreateAnim(L"_IdleRight", m_pTex, Vec2(700.f, 0.f),
		Vec2(70.f, 70.f), Vec2(70.f, 0.f), 1, 0.1f);
	GetAnimator()->PlayAnim(L"_IdleRight",true);

	//// 오프셋 건드리기
	Animation* pAnim = GetAnimator()->FindAnim(L"_IdleRight");
	//// 하나만
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// 프레임 다 
	for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i);
		//pAnim->SetFrameOffset(i, Vec2(0.f, -20.f));
	CreateInit();
}

Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}

void Player::Update()
{
	Object::Update();
	
	if (KEY_DOWN(KEY_TYPE::R))
		ReStart();

	UpdateState();
	UpdateMove();
	
	GetAnimator()->Update();
}

float Player::GetJumpLevel(float& _acc)
{	
	if (_acc < 0.2f)
		return 0;
	else 
		return std::clamp(_acc, 0.5f, 2.f);
}

void Player::Jump()
{
	_isJump = true;

}

void Player::DoubleJump()
{
	_isDoubleJump = true;
	SetShellOff();
}

void Player::Land()
{
}

void Player::CreateInit()
{
	GetGravity()->SetGravity(1400.f);
	GetGravity()->SetApplyGravity(true);
}

void Player::UpdateState()
{
	//std::cout << (int)m_curState;
	if (m_curState == PLAYER_STATE::FALL || m_curState == PLAYER_STATE::JUMP || m_curState == PLAYER_STATE::OFF)
		return;

	if (m_curState == PLAYER_STATE::JUMP)
	{
		float yVelo = GetRigidbody()->GetVelocity().y;

		if (yVelo < 0.f)
		{
			m_curState = PLAYER_STATE::FALL;
		}
	}

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		_dir = -1;
		if (PLAYER_STATE::JUMP != m_curState)
			m_curState = PLAYER_STATE::MOVE;
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		_dir = 1;
		if (PLAYER_STATE::JUMP != m_curState)
			m_curState = PLAYER_STATE::MOVE;
	}

	Vec2 velocity = GetRigidbody()->GetVelocity();
	if (abs(velocity.x) < 0.001f 
		&& abs(velocity.y) < 0.001f 
		&& PLAYER_STATE::JUMP != m_curState)
	{
		m_curState = PLAYER_STATE::IDLE;
	}

	if (KEY_PRESS(KEY_TYPE::SPACE))
	{
		/*GetCollider()->SetOffsetPos(Vector2{ 0.f, 30.f });
		GetCollider()->SetColliderScale(Vector2{ 60.f, 40.f });*/
		m_curState = PLAYER_STATE::CHARGE;
		_acc += fDT;

	}
	else if (KEY_UP(KEY_TYPE::SPACE))
	{
		/*GetCollider()->SetOffsetPos(Vector2{ 0.f, 10.f });
		GetCollider()->SetColliderScale(Vector2{ 60.f, 80.f });*/
		_jumpLevel = GetJumpLevel(_acc);
		std::cout << _jumpLevel;
		if (_jumpLevel == 0) return;

		m_curState = PLAYER_STATE::JUMP;
		_acc = 0;
		ResMgr::GetInst()->LoadSound(L"Jump", L"Sound\\cartoon-jump-6462.wav", false);

		bool left = false;
		bool right = false;

		if (KEY_PRESS(KEY_TYPE::LEFT))
			left = true;
		if (KEY_PRESS(KEY_TYPE::RIGHT))
			right = true;

		if (GetRigidbody())
		{
			// ===================
			// 이단 점프 구현하고 싶을 경우
			/*Vector2 curVel = GetRigidBody()->GetVelocity();
			GetRigidBody()->SetVelocity(Vector2(curVel.x, -200.f));*/
			// ===================

			if (!_isDoubleJump)
			{
				if (!_isJump)
				{
					
					Vec2 dir = Vec2{ 0,0 };
					dir.y = _jumpPower * _jumpLevel;

					if ((left && right) || (!left && !right))
					{
						_dir = 0;
						dir.x = 0;
						dir.y += _jumpPower * _jumpLevel;
					}
					else if (right)
					{
						dir.x = 200.f;
					}
					else if (left)
					{
						dir.x = -200.f;
					}

					GetRigidbody()->AddVelocity(dir);
					Jump();
				}
				else
				{
					GetRigidbody()->SetVelocity({ GetRigidbody()->GetVelocity().x, _jumpPower * _jumpLevel / 2 });
					DoubleJump();
				}
			}
		}
	}
}

void Player::UpdateMove()
{
	if (m_curState == PLAYER_STATE::OFF || m_curState == PLAYER_STATE::FALL || m_curState == PLAYER_STATE::CHARGE)
		return;

	Rigidbody* rb = GetRigidbody();

	if (m_curState == PLAYER_STATE::JUMP)
	{
		rb->SetVelocity(Vec2(200.f * _dir, rb->GetVelocity().y));
	}
	else
	{
		if (KEY_PRESS(KEY_TYPE::LEFT))
		{
			// rd->AddForce(Vector2(-200.f, 0.f));
			rb->SetVelocity(Vec2(-200.f, rb->GetVelocity().y));
		}
		if (KEY_PRESS(KEY_TYPE::RIGHT))
		{
			// rd->AddForce(Vector2(200.f, 0.f));
			rb->SetVelocity(Vec2(200.f, rb->GetVelocity().y));
		}

		if (KEY_DOWN(KEY_TYPE::LEFT))
		{
			// rd->AddVelocity(Vector2(-200.f, 0.f));
			rb->SetVelocity(Vec2(-200.f, rb->GetVelocity().y));

		}
		if (KEY_DOWN(KEY_TYPE::RIGHT))
		{
			// rd->AddVelocity(Vector2(200.f, 0.f));
			rb->SetVelocity(Vec2(200.f, rb->GetVelocity().y));
		}
	}
}

void Player::SetShell()
{
	_shellOn = true;
	m_vScale = Vec2{ 1.1f,1.4f };
}

void Player::SetShellOff()
{
	_shellOn = false;
	m_vScale = Vec2{ 1.f,1.f };
	//m_OffsetPos = 
}

void Player::Render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//int Width = m_pTex->GetWidth();
	//int Height = m_pTex->GetHeight();
	////// 1. 기본 옮기기
	//BitBlt(_dc
	//	,(int)(vPos.x - vScale.x /2)
	//	,(int)(vPos.y - vScale.y /2)
	//	, Width,Height, m_pTex->GetDC()
	//	,0,0,SRCCOPY);

	////// 2. 색상 걷어내기
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,255,255));

	////// 3. 확대 및 축소
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width ,Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, SRCCOPY);

	// 4. 회전
	// 삼각함수, 회전행렬
	//Plgblt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, RGB(255, 0, 255));
	//RECT_RENDER(m_vPos.x, m_vPos.y, m_v->GetWidth() * m_vScale.x, m_tex->GetHeight() * m_vScale.y, _dc);
	Component_Render(_dc);
}

void Player::EnterCollision(Collider* _pOther)
{
	wstring objName = _pOther->GetObj()->GetName();
	
	if ( objName == L"Ground")
	{
		_isGround = CheckColDir(_pOther->GetObj());
		PLAYER_STATE playerState = GetCurState();

		// result == true라면은 땅에 착지한 경우
		if (_isGround)
		{
			ResMgr::GetInst()->LoadSound(L"Land", L"Sound\\land-81509.wav", false);

			if (playerState == PLAYER_STATE::JUMP)
			{
				m_curState = PLAYER_STATE::IDLE;
			}
		}
		else
		{
			ResMgr::GetInst()->LoadSound(L"Bump", L"Sound\\bump.wav", false);

			GetRigidbody()->StopImmediately();
			if (playerState == PLAYER_STATE::FALL)
			{
				if (_dir == -1)
				{
					GetRigidbody()->SetVelocity(Vec2((_dir * -1) * (200.f), 0.f));
				}

				if (_dir == 1)
				{
					GetRigidbody()->SetVelocity(Vec2(_dir * 200.f * -1, 0.f));
				}
			}
			if(playerState == PLAYER_STATE::JUMP)
			{
				if (_dir == -1)
				{
					GetRigidbody()->AddVelocity(Vec2((_dir * -1) * (200.f), 200.f * -1));
				}

				if (_dir == 1)
				{
					GetRigidbody()->AddVelocity(Vec2(_dir * 200.f * -1, 200.f * -1));
				}
			}
			
			m_curState = PLAYER_STATE::OFF;
		}
		
		//if (pGround->GetCollider()->GetFinalPos().y > GetCollider()->GetFinalPos().y) // 플레이어가 위에있을때.
		//{
		//	GetRigidbody()->StopImmediately();
		//	GetGravity()->SetApplyGravity(false);

		//	Vec2 objPos = _pOther->GetFinalPos();
		//	Vec2 objScale = _pOther->GetScale();

		//	Vec2 pos = GetCollider()->GetFinalPos();
		//	Vec2 scale = GetCollider()->GetScale();

		//	float len = abs(pos.y - objPos.y);
		//	float value = (scale.y / 2.f + objScale.y / 2.f) - len;

		//	pos = GetPos();
		//	pos.y += value + 0.1f;
		//	SetPos(pos);

			/*	float pointGap =
					(pGround->GetCollider()->GetFinalPos().y
						- pGround->GetCollider()->GetScale().y / 2);*/
						//SetPos({ GetPos().x, pointGap + 1.f });
			//_isCreateEnd = true;
		
		//else //밑에서 부딪힌 경우
		//{
		//	GetRigidbody()->StopImmediately();
		//}
	}
}

void Player::ExitCollision(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Ground")
	{
		GetGravity()->SetApplyGravity(true);
		PLAYER_STATE playerState = m_curState;

		if (_isGround)
		{
			if (playerState == PLAYER_STATE::MOVE || playerState == PLAYER_STATE::IDLE)
				m_curState = PLAYER_STATE::FALL;
		}
		_isGround = false;
	}
	
}

void Player::StayCollision(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Ground")
	{
		_isGround = true;
		_isJump = false;
		_isDoubleJump = false;
	}
}

bool Player::CheckColDir(Object* otherObj)
{
	PLAYER_STATE playerState = GetCurState();

	Ground* ground = reinterpret_cast<Ground*>(otherObj);

	Vec2 playerPos = GetCollider()->GetFinalPos();
	Vec2 playerScale = GetCollider()->GetScale();

	Vec2 groundPos = otherObj->GetCollider()->GetFinalPos();
	Vec2 groundScale = otherObj->GetCollider()->GetScale();

	float playerRightPosX = playerPos.x + (playerScale.x / 2.f);
	float playerLeftPosX = playerPos.x - (playerScale.x / 2.f);
	float playerTopPosY = playerPos.y - (playerScale.y / 2.f);
	float playerBottomPosY = playerPos.y + (playerScale.y / 2.f);

	float groundRightPosX = groundPos.x + (groundScale.x / 2.f);
	float groundLeftPosX = groundPos.x - (groundScale.x / 2.f);
	float groundTopPosY = groundPos.y - (groundScale.y / 2.f);
	float groundBottomPosY = groundPos.y + (groundScale.y / 2.f);

	// ground 위쪽면 부딪힐 경우(플레이어가 땅위에 서 있을 경우
	if (playerBottomPosY + 5 >= groundTopPosY && playerPos.y < groundTopPosY)
	{
		if (playerRightPosX <= (groundRightPosX + groundScale.x / 2.f) && playerLeftPosX >= groundLeftPosX - (groundScale.x / 2.f))
		{
			return true;
		}
	}

	// ground 왼쪽면 부딪힐 경우
	if (playerRightPosX >= groundLeftPosX && playerPos.x < groundLeftPosX)
	{
		if (groundTopPosY - (groundScale.y / 2.f) < playerTopPosY && groundBottomPosY + (groundScale.y / 2.f) > playerBottomPosY)
		{
			return false;
		}
	}

	// ground 오른쪽면 부딪힐 경우
	if (playerLeftPosX <= groundRightPosX && playerPos.x > groundRightPosX)
	{
		if (groundTopPosY - (groundScale.y / 2.f) < playerTopPosY && groundBottomPosY + (groundScale.y / 2.f) > playerBottomPosY)
		{
			return false;
		}
	}

	// ground 아랫면 부딪힐 경우
	if (playerTopPosY <= groundBottomPosY && playerPos.y > groundBottomPosY)
	{
		if (playerRightPosX <= (groundRightPosX + groundScale.x / 2.f) && playerLeftPosX >= groundLeftPosX - (groundScale.x / 2.f))
		{
			return false;
		}
	}
}
