#pragma once
//#include "Object.h"
class Object;
class Scene
{
public:
	Scene();
	virtual ~Scene();
	// Init(), Update(), Render(), Release();
	virtual void Init() abstract;
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);
	virtual void Release();
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
public:
	const vector<Object*>& GetGroupObject(OBJECT_GROUP _etype) const
	{
		return m_vecObj[(UINT)_etype];
	}
public:
	void AddObject(Object* _pObj, OBJECT_GROUP _eType)
	{
		m_vecObj[(UINT)_eType].push_back(_pObj);
	}
	void ADDBG(Object* _pObj)
	{
		m_bgObj = _pObj;
	}
private:
//	Object*  m_obj;
	vector<Object*> m_vecObj[(UINT)OBJECT_GROUP::END];
	Object* m_bgObj;
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
};

