#pragma once
class Camera;
class CameraMgr
{
	SINGLE(CameraMgr);
public:
	void Init();
	void Update();
	void Render(HDC _dc);
public:
	void SetLook(Vec2 _v) { m_vLook = _v; }
	void SetObj(Object* _pObj) { m_pObj = _pObj; }
	const Vec2& GetLocalPos(Vec2 _objPos) const
	{
		return _objPos - m_vDiff;
	}
	const Vec2& GetRealPos(Vec2 _vLookPos) const
	{
		return _vLookPos + m_vDiff;
	}

private:
	//vector<Camera*> cams;
	Camera* _mainCam;
	Vec2	m_vLook;
	Object* m_pObj;
	Vec2	m_vDiff;
};

