#pragma once

class MapObject;
#include "Texture.h"
#include "tileson.h"

class MapMgr
{
	SINGLE(MapMgr);

public:
	void Init();
	void CreateJsonBoard();
	MapObject* StoreAndLoadImage(const std::string & _image, const Vec2 _pos);
public:
	std::string WstrToStr(const std::wstring& source);
	std::wstring StrToWstr(const std::string& source);
	const vector<MapObject*>& GetMapObjs() const { return m_mapObjs; }
private:
	tson::Tileson m_tson;
	std::shared_ptr<tson::Map> m_uptrMap;
	std::map<std::string, std::shared_ptr<Texture>> m_maptex;
	std::map<std::string, MapObject*> m_mapsprite;

	std::vector<MapObject*> m_mapObjs;
	tson::Map* m_curMap;
};