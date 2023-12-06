#include "pch.h"
#include "MapMgr.h"
#include "MapObject.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "tileson.hpp"
#include "Texture.h"
#include "ResMgr.h"
#include "Core.h"


void MapMgr::Init()
{
	//BackGroundLayer
	//ObjectLayer
	//std::cout << fs::absolute(fs::path("./"));
	m_uptrMap = m_tson.parse(fs::path("./Map/JumpMapChange.json"));
	if (m_uptrMap->getStatus() != tson::ParseStatus::OK)
	{
		std::cout << "json file error " << std::endl;
	}
}

void MapMgr::CreateJsonBoard()
{
	if (m_uptrMap->getStatus() == tson::ParseStatus::OK)
	{
		int a = 0;
		tson::Layer* fg = m_uptrMap->getLayer("FG");
		tson::Layer* bg = m_uptrMap->getLayer("BG");
		tson::Layer* bgLayer = &bg->getLayers()[0];
		tson::Layer* ShellLayer = &fg->getLayers()[0];
		tson::Layer* objLayer = &fg->getLayers()[1];

		for (auto& obj : objLayer->getObjects())
		{
			tson::Vector2i pos = obj.getPosition();
			if (obj.getName() == "Mario")
			{
				//마리오 세팅

			}
		}
		for (auto& [pos, tileObject] : bgLayer->getTileObjects())
		{
			tson::Tileset* tileset = tileObject.getTile()->getTileset();
			tson::Rect rect = tileObject.getDrawingRect();
			tson::Vector2f realposition = tileObject.getPosition();
			Object* sprite = StoreAndLoadImage(tileset->getImage().u8string(), { 0,0 });
			if (sprite != nullptr)
			{
				sprite->SetTextureRect({ rect.x, rect.y, rect.width, rect.height });
				sprite->SetPos({});
			}
		}
	}
}

Object* MapMgr::StoreAndLoadImage(const std::string& _image, const Vec2 _pos)
{
	fs::path path = _image;
	if (m_maptex.count(_image) == 0)
	{
		if (fs::exists(path) && fs::is_regular_file(path))
		{
			Texture* tex = ResMgr::GetInst()->TexFind(L"Map");
			bool imageFound = tex->LoadFromFile(StrToWstr(path.generic_string()));
			if (imageFound)
			{
				Object* spr = new Object;
				spr->SetTexture(tex);
				spr->SetPos(_pos);
				m_maptex[_image] = std::move(tex);
				m_mapsprite[_image] = std::move(spr);
			}
		}
		else
		{
			std::cout << "can't find" << path.generic_string() << std::endl;
		}
	}
	if (m_mapsprite.count(_image) > 0)
		return m_mapsprite[_image];
	return nullptr;
}

void MapMgr::Render()
{
	m_curMap = m_uptrMap.get();
	if (m_curMap != nullptr)
	{
		for (auto& layer : m_curMap->getLayers())
			RenderLayers(layer);
	}
}

void MapMgr::RenderLayers(tson::Layer& layer)
{
	switch (layer.getType())
	{
	case::tson::LayerType::TileLayer:
		RenderTileLayer(layer);
		break;
	case::tson::LayerType::ObjectGroup:
		break;
	case::tson::LayerType::ImageLayer:
		break;
	default:
		break;
	}
}

void MapMgr::RenderTileLayer(tson::Layer& layer)
{
	for (auto& [pos, tileObj] : layer.getTileObjects()) {
		tson::Tileset* tileSet = tileObj.getTile()->getTileset();
		tson::Rect rect;

		bool isAnimation = tileObj.getTile()->getAnimation().any();
		if (!isAnimation) {
			rect = tileObj.getDrawingRect();
		}
		else {
			UINT tileId = tileObj.getTile()->getId();
			if (m_maptsonAnim.count(tileId) == 0) {
				m_maptsonAnim[tileId] = &tileObj.getTile()->getAnimation();
			}


			UINT curId = tileObj.getTile()->getAnimation().getCurrentTileId();
			tson::Tile* animationTile;
			for (auto& [id, animation] : m_maptsonAnim) {
				animationTile = tileSet->getTile(1);
				rect = animationTile->getDrawingRect();
			}

			for (auto& [id, animation] : m_maptsonAnim)
			{
				std::cout << "Frame: " << animation->getCurrentFrameNumber() << "Duration: " << animation->getCurrentFrame()->getDuration()
					<< "Tile: " << animation->getCurrentTileId() << std::endl;
				tileId = animation->getCurrentTileId();
				if (tileId)
					break;
			}
		}

		tson::Vector2f realPos = tileObj.getPosition();
		tson::Vector2i imageSize = tileSet->getImageSize();
		Object* sprite = StoreAndLoadImage(tileSet->getImage().u8string(), { 0, 0 });

		//	// texture 입히기
		sprite->SetTextureRect({ rect.x, rect.y, rect.width, rect.height });

		//	// origin 세팅
			Vec2 origin = { (float)rect.width / 2.f, (float)rect.height / 2.f };
		//	sprite->setOrigin(origin);

		//	// position 세팅
			realPos = { realPos.x + origin.x, realPos.y + origin.y };
			sprite->SetPos({ realPos.x, realPos.y });

			sprite->Render(Core::GetInst()->GetMainDC());
		//	GET_WINDOW.draw(*sprite);
		//}
	}
}

void MapMgr::UpdateTileAnimation(float _dt)
{
	for (auto& [id, animation] : m_maptsonAnim)
	{
		animation->update(_dt * 1000);
	}
}

//void MapMgr::MakeObject(MAPOBJECT_TYPE _type)
//{
//	//MapObject* obj = new MapObject(_type);
//	//obj->SetPos(Vec2{ WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 });
//	//m_mapObjs.push_back(obj);
//}
//
//
//void MapMgr::MovingObject()
//{
//	if (m_currentSelectObj == NULL) return;
//	m_currentSelectObj->SetPos(m_mouseObj->GetPos());
//}
//
//void MapMgr::ReleaseObject()
//{
//	m_currentSelectObj->SetIsClicked(false);
//	m_currentSelectObj = NULL;
//}

//void MapMgr::SaveObjectInfo(int idx)
//{
//
//}

//void MapMgr::LoadObjectInfo()
//{
//}
//
//Object* MapMgr::FindObject(Vec2 m_mousePos)
//{
//	for (int i = 0; i < m_mapObjs.size(); i++)
//	{
//		if (CollisionMgr::GetInst()->CheckContainObject(m_mousePos, m_mapObjs[i]->GetCollider()))
//		{
//			return m_mapObjs[i];
//		}
//	}
//	return NULL;
//}

void MapMgr::Update()
{
	/*m_mouseObj->SetPos(KeyMgr::GetInst()->GetMousePos());
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
	MovingObject();*/
}

void MapMgr::Render(HDC _dc)
{
	/*for (auto& object : m_mapObjs)
	{
		object->Render(_dc);
	}*/
}
