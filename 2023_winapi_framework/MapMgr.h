#pragma once

class Object;
#include "Texture.h"
#include "tileson.h"
#include <string>

class MapMgr
{
	SINGLE(MapMgr);

public:
	void Init();
	void CreateJsonBoard();
	std::shared_ptr<Object> StoreAndLoadImage(const std::string & _image, const Vec2 _pos);
	void Render();
	void RenderLayers(tson::Layer& layer);
	void RenderTileLayer(tson::Layer& layer);
	void UpdateTileAnimation(float _dt);
public:
	std::string WstrToStr(const std::wstring& source);
	std::wstring StrToWstr(const std::string& source);
public:
	void Update();
	void Render(HDC _dc);
private:
	tson::Tileson m_tson;
	std::shared_ptr<tson::Map> m_uptrMap;
	std::map<std::string, std::shared_ptr<Texture>> m_maptex;
	std::map<std::string, std::shared_ptr<Object>> m_mapsprite;
	tson::Map* m_curMap;
	std::map<UINT, tson::Animation*> m_maptsonAnim;
};