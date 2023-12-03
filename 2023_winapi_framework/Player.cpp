#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
Player::Player()
	: m_pTex(nullptr)
{
	//m_pTex = new Texture;
	//wstring strFilePath = PathMgr::GetInst()->GetResPath();
	//strFilePath += L"Texture\\plane.bmp";
	//m_pTex->Load(strFilePath);
	//m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\plane.bmp");
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jiwoo.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	_gravityScale = 9.8f;
	_jumpPower = 100;

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
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// 하나만
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// 프레임 다 
	//for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->SetFrameOffset(i, Vec2(0.f, 20.f));
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	Vec2 vPos = GetPos();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		vPos.x -= 100.f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		vPos.x += 100.f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}

	if (_isGround && KEY_DOWN(KEY_TYPE::SPACE) && !_isDoubleJump)
	{
		if (_isJump) //DoubleJump
		{
			DoubleJump();
		}
		else
		{
			Jump();
		}
	}
	else
	{
		
	}


	_moveDir.y -= _gravityScale * fDT;

	vPos = vPos + _moveDir;

	_isGround = CheckGroundCollider(vPos.y);

	/*if(KEY_PRESS(KEY_TYPE::CTRL))
		GetAnimator()->PlayAnim(L"Jiwoo_Attack", false, 1);*/
	SetPos(vPos);
	GetAnimator()->Update();
}

void Player::Jump()
{
	_isJump = true;
	_moveDir.y += _jumpPower;
}

void Player::DoubleJump()
{
	_isDoubleJump = true;
	_moveDir.y += _jumpPower * 0.8f;
}

bool Player::CheckGroundCollider(float yValue)
{
	return
}

void Player::Land()
{
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


