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
	, _isJump(false)
	, _isDoubleJump(false)
	, _jumpPower(-800.f)
	, _isGround(true)
	, _moveDir{ 0.0f,0.0f }
	, _jumpTime{ 0.f }
	, _curTime{ 0.f }
	, _isCreateEnd{ false }
{
	//m_pTex = new Texture;
	//wstring strFilePath = PathMgr::GetInst()->GetResPath();
	//strFilePath += L"Texture\\plane.bmp";
	//m_pTex->Load(strFilePath);
	//m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\plane.bmp");
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jiwoo.bmp");
	CreateCollider();
	CreateRigidbody();
	CreateGravity();
	GetGravity()->SetApplyGravity(false);
	GetCollider()->SetScale(Vec2(20.f,30.f));
	//GetCollider()->SetOffSetPos(Vec2(0.f,-20.f));
	
	CreateAnimator();
	GetAnimator()->CreateAnim(L"Jiwoo_Front", m_pTex,Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Back", m_pTex, Vec2(0.f, 100.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Left", m_pTex, Vec2(0.f, 0.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Right", m_pTex, Vec2(0.f, 50.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Attack", m_pTex, Vec2(0.f, 200.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->PlayAnim(L"Jiwoo_Front",true);

	//// 오프셋 건드리기
	Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
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
	if (_isCreateEnd == false)
	{
		return;
	}
	else
	{
		GetGravity()->SetGravity(1600.f);
	}

	Rigidbody* rb = GetRigidbody();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		rb->SetVelocity(Vec2(-300.f, rb->GetVelocity().y));
		//vPos.x -= 100.f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		rb->SetVelocity(Vec2(300.f, rb->GetVelocity().y));
		//vPos.x += 100.f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}

	if (KEY_DOWN(KEY_TYPE::SPACE))
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
				DoubleJump();
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
	GetRigidbody()->SetVelocity({ 0.f, _jumpPower * 0.8f });
}

void Player::Land()
{
}

void Player::CreateInit()
{
	GetGravity()->SetGravity(200.f);
	GetGravity()->SetApplyGravity(true);
}

void Player::Render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//int Width = m_pTex->GetWidth();
	//int Height = m_pTex->GetHeight();
	//// 1. 기본 옮기기
	//BitBlt(_dc
	//	,(int)(vPos.x - vScale.x /2)
	//	,(int)(vPos.y - vScale.y /2)
	//	, Width,Height, m_pTex->GetDC()
	//	,0,0,SRCCOPY);

	//// 2. 색상 걷어내기
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,0,255));

	//// 3. 확대 및 축소
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
	Component_Render(_dc);
}

void Player::EnterCollision(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Ground")
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


