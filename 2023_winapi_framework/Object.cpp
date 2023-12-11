#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Gravity.h"
#include "Texture.h"

Object::Object()
	: m_pCollider(nullptr)
	, m_vPos{}
	, m_vScale{}
	, m_IsAlive(true)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
	, m_pGravity(nullptr)
	, m_texRect({0,0,0,0})
	, m_tex(nullptr)
{
}

Object::~Object()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pRigidbody)
		delete m_pRigidbody;
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
	if (nullptr != m_pGravity)
		delete m_pGravity;
	//delete m_tex;
}

//bool Object::CheckInclude(Object obj1, Object obj2)
//{
	//obj1.
	//return false;
//}

void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void Object::CreateRigidbody()
{
	m_pRigidbody = new Rigidbody;
	m_pRigidbody->m_pOwner = this;
}

void Object::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void Object::CreateGravity()
{
	m_pGravity = new Gravity;
	m_pGravity->m_pOwner = this;
}

void Object::Update()
{
	//Vec2 vPos = m_obj.GetPos();

//	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//	if(KeyMgr::GetInst()->GetKey(KEY_TYPE::LEFT) == KEY_STATE::UP)

	//m_obj.SetPos(vPos);
}

void Object::FinalUpdate()
{
	if (m_pAnimator)
		m_pAnimator->FinalUpdate();
	if (m_pGravity)
		m_pGravity->FinalUpdate();
	if (m_pRigidbody)
		m_pRigidbody->FinalUpdate(fDT);
	if (m_pCollider)
		m_pCollider->FinalUpdate();
}

void Object::Render(HDC _dc)
{
	/*Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();*/

	if (m_texRect.bottom == 0 && m_texRect.left == 0 && m_texRect.right == 0 && m_texRect.top == 0)
	{

	}
	else
	{
		int Width = m_texRect.right - m_texRect.left;
		int Height = m_texRect.top - m_texRect.bottom;
		TransparentBlt(_dc
			, (int)(m_vPos.x - m_vScale.x / 2)
			, (int)(m_vPos.y - m_vScale.y / 2)
			, Width, Height, m_tex->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
	}
	
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}

void Object::EnterCollision(Collider* _pOther)
{
}

void Object::ExitCollision(Collider* _pOther)
{
}

void Object::StayCollision(Collider* _pOther)
{

}

void Object::Component_Render(HDC _dc)
{
	if (nullptr != m_pCollider)
		m_pCollider->Render(_dc);
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);
}

