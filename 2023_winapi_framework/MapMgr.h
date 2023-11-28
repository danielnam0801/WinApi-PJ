#pragma once

class Object;
class MapMgr
{
	SINGLE(MapMgr);
public:
	void MakeObject(MAPOBJECT_TYPE _type);
	void MovingObject();
	void ReleaseObject();
	//void SaveObjectInfo();
	void LoadObjectInfo();
	Object* FindObject(Vec2 m_mousePos);
public:
	void Update();
	void Render(HDC _dc);
private:
	Object* m_mouseObj;
	Object* m_currentSelectObj;
	vector<Object*> m_mapObjs;
	FILE* mapFile;
};