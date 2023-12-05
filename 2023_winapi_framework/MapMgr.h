#pragma once

class MapObject;
class MapMgr
{
	SINGLE(MapMgr);
public:
	void Init();
	void CreateJsonBoard();
	MapObject* StoreAndLoadImage(const std::string& _image
		, const Vec2 _pos);
	void Render();
	void RenderLayers(tson::Layer& layer);
	void RenderTileLayer(tson::Layer& layer);
	void UpdateTileAnimation(float _dt);
public:
	//void MakeObject(MAPOBJECT_TYPE _type);
	//void MovingObject();
	//void ReleaseObject();
	//void SaveObjectInfo();
	//void LoadObjectInfo();
	//Object* FindObject(Vec2 m_mousePos);
public:
	void Update();
	void Render(HDC _dc);
private:
	//Object* m_mouseObj;
	//Object* m_currentSelectObj;
	//vector<Object*> m_mapObjs;
	tson::Tileson m_tson;
	std::unique_ptr<tson::Map> m_uptrMap;
	std::map<std::string, std::unique_ptr<Texture>> m_maptex;
	std::map<std::string, std::unique_ptr<MapObject>> m_mapsprite;
	tson::Map* m_curMap;
	std::map<UINT, tson::Animation*> m_maptsonAnim;
};