#include "pch.h"
#include "Ground.h"
#include "Collider.h"

Ground::Ground()
{
	CreateCollider();
	GetCollider()->SetScale({ 1000.f, 100.f });
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
	
}

void Ground::StayCollision(Collider* other)
{
}
