#pragma once

class Object;
class MapMgr
{
	SINGLE(MapMgr);
public:
	void MakeObject(MAPOBJECT_TYPE _type);
	void MovingObject();
	void FindObject();
private:
	Object* m_mouseObj;
	vector<Object*> m_mapObjs;
};

