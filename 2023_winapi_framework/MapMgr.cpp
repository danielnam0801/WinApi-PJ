#include "pch.h"
#include "MapMgr.h"
#include "MapObject.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"

void MapMgr::MakeObject(MAPOBJECT_TYPE _type)
{
	//MapObject* obj = new MapObject(_type);
	//obj->SetPos(Vec2{ WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 });
	//m_mapObjs.push_back(obj);
}

void MapMgr::MovingObject()
{
	if (m_currentSelectObj == NULL) return;
	m_currentSelectObj->SetPos(m_mouseObj->GetPos());
}

void MapMgr::ReleaseObject()
{
	m_currentSelectObj->SetIsClicked(false);
	m_currentSelectObj = NULL;
}

//void MapMgr::SaveObjectInfo(int idx)
//{
//
//}

void MapMgr::LoadObjectInfo()
{
}

Object* MapMgr::FindObject(Vec2 m_mousePos)
{
	for (int i = 0; i < m_mapObjs.size(); i++)
	{
		if (CollisionMgr::GetInst()->CheckContainObject(m_mousePos, m_mapObjs[i]->GetCollider()))
		{
			return m_mapObjs[i];
		}
	}
	return NULL;
}

void MapMgr::Update()
{
	m_mouseObj->SetPos(KeyMgr::GetInst()->GetMousePos());
	if(KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN)
	{
		m_currentSelectObj = FindObject(m_mouseObj->GetPos());
		if (m_currentSelectObj != NULL)
		{
			m_mouseObj->SetIsClicked(true);
			m_currentSelectObj->SetIsClicked(true);
		}
	}
	else if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::UP)
	{
		if(m_currentSelectObj != NULL)
			ReleaseObject();
	}
	MovingObject();
}

void MapMgr::Render(HDC _dc)
{
	for (auto& object : m_mapObjs)
	{
		object->Render(_dc);
	}
}
