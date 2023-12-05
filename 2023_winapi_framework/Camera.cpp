#include "pch.h"
#include "Camera.h"
#include "Collider.h"
#include "Core.h"

Camera::Camera()
{
	CreateCollider();
	GetCollider()->SetScale(Core::GetInst()->GetResolution());
}

void Camera::Update()
{
	
}

void Camera::CameraMove()
{
}

void Camera::EnterCollision(Collider* _pOther)
{
}

void Camera::ExitCollision(Collider* _pOther)
{
}

void Camera::StayCollision(Collider* _pOther)
{
}
