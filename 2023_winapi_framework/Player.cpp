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
#include "Ground.h"

Player::Player()
	: m_pTex(nullptr)
	, _isJump(false)
	, _isDoubleJump(false)
	, _jumpPower(-5.f)
	, _isGround(false)
	, _moveDir{ 0.0f,0.0f }
{
	//m_pTex = new Texture;
	//wstring strFilePath = PathMgr::GetInst()->GetResPath();
	//strFilePath += L"Texture\\plane.bmp";
	//m_pTex->Load(strFilePath);
	//m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\plane.bmp");
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jiwoo.bmp");
	CreateCollider();
	CreateRigidbody();
	GetRigidbody()->SetApplyGravity(true);
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

	//// ������ �ǵ帮��
	Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// �ϳ���
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// ������ �� 
	for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i);
		//pAnim->SetFrameOffset(i, Vec2(0.f, -20.f));
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	Rigidbody* rb = GetRigidbody();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		rb->AddForce(Vec2(-20.f, 0.f));
		//vPos.x -= 100.f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		rb->AddForce(Vec2(20.f, 0.f));
		//vPos.x += 100.f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}

	if (_isGround && KEY_DOWN(KEY_TYPE::SPACE))
	{
		Jump();	
	}

	if (KEY_DOWN(KEY_TYPE::SPACE))
	{
		if (!_isDoubleJump)
		{
			if (_isGround)
			{
				Jump();
			}
			else if(_isJump)
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
	GetRigidbody()->AddForce({ 0.f, _jumpPower });
}

void Player::DoubleJump()
{
	_isDoubleJump = true;
	GetRigidbody()->AddForce({ 0.f, _jumpPower * 0.8f });
}

//bool Player::CheckGroundCollider()
//{
//	//return 
//	return true;
//}

void Player::Land()
{
}

void Player::Render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//int Width = m_pTex->GetWidth();
	//int Height = m_pTex->GetHeight();
	//// 1. �⺻ �ű��
	//BitBlt(_dc
	//	,(int)(vPos.x - vScale.x /2)
	//	,(int)(vPos.y - vScale.y /2)
	//	, Width,Height, m_pTex->GetDC()
	//	,0,0,SRCCOPY);

	//// 2. ���� �Ⱦ��
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,0,255));

	//// 3. Ȯ�� �� ���
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width ,Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, SRCCOPY);

	// 4. ȸ��
	// �ﰢ�Լ�, ȸ�����
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
		if (pGround->GetCollider()->GetFinalPos().y > GetCollider()->GetFinalPos().y) // �÷��̾ ����������.
		{
			GetRigidbody()->StopImmediately();
			GetRigidbody()->SetApplyGravity(false);

			Vec2 objPos = _pOther->GetFinalPos();
			Vec2 objScale = _pOther->GetScale();

			Vec2 pos = GetCollider()->GetFinalPos();
			Vec2 scale = GetCollider()->GetScale();

			float len = abs(pos.y - objPos.y);
			float value = (scale.y / 2.f + objScale.y / 2.f) - len;
			
			pos = GetPos();
			pos.y += value + 0.1f;
			SetPos(pos);

			_isJump = false;
			_isDoubleJump = false;
			
		/*	float pointGap =
				(pGround->GetCollider()->GetFinalPos().y
					- pGround->GetCollider()->GetScale().y / 2);*/
			//SetPos({ GetPos().x, pointGap + 1.f });
			_isGround = true;
		}
		else //�ؿ��� �ε��� ���
		{
			//GetRigidbody()->StopImmediately();
		}
	}
}

void Player::ExitCollision(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Ground")
	{
		GetRigidbody()->SetApplyGravity(true);
		_isGround = false;
	}
}

void Player::StayCollision(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Ground")
	{
		_isGround = true;
	}
}


