#pragma once

class MapObject;
#include "Texture.h"
#include "tileson.h"
#include <string>

class MapMgr
{
	SINGLE(MapMgr);

public:
	void Init();
	void CreateJsonBoard();
	std::shared_ptr<MapObject> StoreAndLoadImage(const std::string & _image, const Vec2 _pos);
	void Render();
	void RenderLayers(tson::Layer& layer);
	void RenderTileLayer(tson::Layer& layer);
	void UpdateTileAnimation(float _dt);
public:
	std::string WstrToStr(const std::wstring& source);
	std::wstring StrToWstr(const std::string& source);
	const vector<std::shared_ptr<MapObject>>& GetMapObjs() const { return m_mapObjs; }
public:
	void Update();
	void Render(HDC _dc);
private:
	tson::Tileson m_tson;
	std::shared_ptr<tson::Map> m_uptrMap;
	std::map<std::string, std::shared_ptr<Texture>> m_maptex;
	std::map<std::string, std::shared_ptr<MapObject>> m_mapsprite;

	std::vector<std::shared_ptr<MapObject>> m_mapObjs;
	tson::Map* m_curMap;
	std::map<UINT, tson::Animation*> m_maptsonAnim;
	std::shared_ptr<MapObject> m_sprite;
};