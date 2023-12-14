#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "CollisionMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "Gravity.h"
#include "Ground.h"

Player::Player()
	: m_pTex(nullptr)
	, m_idleTex(nullptr)
	, _isJump(false)
	, _isDoubleJump(false)
	, _jumpPower(-1000.f)
	, _isGround(true)
	, _moveDir{ 0.0f,0.0f }
	, _jumpTime{ 0.f }
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
	Rigidbody* rb = GetRigidbody();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		rb->SetVelocity(Vec2(-200.f, rb->GetVelocity().y));
		//vPos.x -= 100.f * fDT;
		GetAnimator()->PlayAnim(L"_IdleLeft", true);
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		rb->SetVelocity(Vec2(200.f, rb->GetVelocity().y));
		//vPos.x += 100.f * fDT;
		GetAnimator()->PlayAnim(L"_IdleRight", true);
	}

	if (KEY_PRESS(KEY_TYPE::SPACE))
	{
		_jumpPower += 0.1f;
	}
	else
	{
		if (_isGround)
		{
			
		}
	}

	if (KEY_UP(KEY_TYPE::SPACE))
	{
		if (!_isDoubleJump)
		{
			//GetGravity()->SetApplyGravity(true);
			if (_isGround)
			{
				Jump();
			}
			else
			{
				if (_shellOn)
				{
					DoubleJump();
					SetShellOff();
				}
			}
			if (KEY_PRESS(KEY_TYPE::RIGHT))
			{
				GetAnimator()->PlayAnim(L"Jump_Right", true);
				rb->AddVelocity(Vec2(200.f, rb->GetVelocity().y));
			}
			else if (KEY_PRESS(KEY_TYPE::LEFT))
			{
				GetAnimator()->PlayAnim(L"Jump_Left", true);
				rb->AddVelocity(Vec2(-200.f, rb->GetVelocity().y));
			}
		}
	}


	//_moveDir.y -= _gravityScale * fDT;

	//vPos = vPos + _moveDir;


	/*if(KEY_PRESS(KEY_TYPE::CTRL))
		GetAnimator()->PlayAnim(L"Jiwoo_Attack", false, 1);*/
	//SetPos(vPos);
	GetAnimator()->Update();
}

void Player::Jump()
{
	_isJump = true;
	GetRigidbody()->SetVelocity({ 0.f, _jumpPower });
}

void Player::DoubleJump()
{
	_isDoubleJump = true;
	GetRigidbody()->SetVelocity({ 0.f, _jumpPower * 0.8f});
}

void Player::Land()
{
}

void Player::CreateInit()
{
	GetGravity()->SetGravity(1400.f);
	GetGravity()->SetApplyGravity(true);
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
	//RECT_RENDER(m_vPos.x, m_vPos.y, m_tex->GetWidth() * m_vScale.x, m_tex->GetHeight() * m_vScale.y, _dc);
	Component_Render(_dc);
}

void Player::EnterCollision(Collider* _pOther)
{
	wstring objName = _pOther->GetObj()->GetName();
	
	if ( objName == L"Ground")
	{
		Ground* pGround = reinterpret_cast<Ground*>(_pOther->GetObj());
		if (pGround->GetCollider()->GetFinalPos().y > GetCollider()->GetFinalPos().y) // 플레이어가 위에있을때.
		{
			GetRigidbody()->StopImmediately();
			GetGravity()->SetApplyGravity(false);

			Vec2 objPos = _pOther->GetFinalPos();
			Vec2 objScale = _pOther->GetScale();

			Vec2 pos = GetCollider()->GetFinalPos();
			Vec2 scale = GetCollider()->GetScale();

			float len = abs(pos.y - objPos.y);
			float value = (scale.y / 2.f + objScale.y / 2.f) - len;

			pos = GetPos();
			pos.y += value + 0.1f;
			SetPos(pos);

			/*	float pointGap =
					(pGround->GetCollider()->GetFinalPos().y
						- pGround->GetCollider()->GetScale().y / 2);*/
						//SetPos({ GetPos().x, pointGap + 1.f });
			_isGround = true;
			_isCreateEnd = true;
		}
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


