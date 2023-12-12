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
#include "PathMgr.h"
#include "Collider.h"
#include "Core.h"


void MapMgr::Init()
{
	//BackGroundLayer
	//ObjectLayer
	//std::cout << fs::absolute(fs::path("./"));
	
	m_uptrMap = m_tson.parse(fs::path("./Map/4JumpMapChange.json"));
	if (m_uptrMap->getStatus() != tson::ParseStatus::OK)
	{
		std::cout << "json file error " << std::endl;
	}
}

void MapMgr::CreateJsonBoard()
{
	if (m_uptrMap->getStatus() == tson::ParseStatus::OK)
	{
		//tson::Layer* bgLayer = m_uptrMap->getLayer("BackGroundLayer");
		tson::Layer* ShellLayer = m_uptrMap->getLayer("ShellLayer");;
		tson::Layer* objLayer = m_uptrMap->getLayer("ObjectLayer");;

		for (auto& [pos, tileObject] : objLayer->getTileObjects())
		{
			//tson::Tileset* tileSet = tileObject.getTile()->getTileset();
			//tson::Rect rect = tileObject.getDrawingRect();

			//tson::Vector2f realPos = tileObject.getPosition();
			//tson::Vector2i imageSize = tileSet->getImageSize();
			//std::string path = tileSet->getImage().u8string();
			//path = PathMgr::GetInst()->GetPathWithOutRes(path);
			//path = PathMgr::GetInst()->ReplaceAll(path, "/", "\\");
			//MapObject* image = StoreAndLoadImage(path, { 0, 0 });
			//MapObject* sprite = new MapObject;
			//sprite->DeepCopy(image);

			//delete image;

			//Vec2 m_Scale = { 1.5f, 1.5f };

			//sprite->SetTextureRect({ rect.x, rect.y, rect.width , rect.height });

			//sprite->SetScale(m_Scale);
			//////	// origin 技泼
			////Vec2 origin = { 0.f, 0.f };
			//Vec2 origin = { (float)rect.width / 2.f, (float)rect.height / 2.f };
			//origin *= m_Scale;
			//sprite->GetCollider()->SetOffSetPos(origin);
			//Vec2 size = Vec2((float)rect.width, (float)rect.height);
			//size *= m_Scale;
			//sprite->GetCollider()->SetScale(size);
			//////	// position 技泼
			//realPos = { (realPos.x + origin.x) * m_Scale.x , (realPos.y + origin.y) * m_Scale.y };
			//sprite->SetPos({ realPos.x, realPos.y });
			//m_mapObjs.push_back(sprite);

		}

		for (auto& [pos, tileObject] : objLayer->getTileObjects())
		{
			tson::Tileset* tileSet = tileObject.getTile()->getTileset();
			tson::Rect rect = tileObject.getDrawingRect();

			tson::Vector2f realPos = tileObject.getPosition();
			tson::Vector2i imageSize = tileSet->getImageSize();
			std::string path = tileSet->getImage().u8string();
			path = PathMgr::GetInst()->GetPathWithOutRes(path);
			path = PathMgr::GetInst()->ReplaceAll(path, "/", "\\");
			MapObject* image = StoreAndLoadImage(path, { 0, 0 });
			MapObject* sprite = new MapObject;
			sprite->DeepCopy(image);

			Vec2 m_Scale = { 1.5f, 1.5f };

			sprite->SetTextureRect({ rect.x, rect.y, rect.width , rect.height });

			sprite->SetScale(m_Scale);
			sprite->SetName(L"MapObject");
			////	// origin 技泼

			Vec2 origin = { (float)rect.width / 2.f, (float)rect.height / 2.f };
			origin *= m_Scale;
			sprite->GetCollider()->SetOffSetPos(origin);
			
			////	// position 技泼
			realPos = { (realPos.x + origin.x) * m_Scale.x , (realPos.y + origin.y) * m_Scale.y };
			sprite->SetPos({ realPos.x, realPos.y });
			m_mapObjs.push_back(sprite);
				
			////	// collider 技泼
			Vec2 size = Vec2((float)rect.width, (float)rect.height);
			size *= m_Scale;
			sprite->GetCollider()->SetScale(size);

		}
	}
}

MapObject* MapMgr::StoreAndLoadImage(const std::string& _image, const Vec2 _pos)
{
	fs::path path = _image;
	if (m_maptex.count(_image) == 0)
	{
		//if (fs::exists(path) && fs::is_regular_file(path))
	
			std::shared_ptr<Texture> tex = ResMgr::GetInst()->TexLoad(StrToWstr(_image), path);
			//bool imageFound = tex->LoadFromFile(tex->GetRelativePath());
			if (tex != nullptr)
			{
				MapObject* spr = new MapObject;
				spr->SetTexture(tex);
				m_maptex[_image] = tex;
				m_mapsprite[_image] = spr;
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


std::string MapMgr::WstrToStr(const std::wstring& source)
{
	return std::string().assign(source.begin(), source.end());
}

std::wstring MapMgr::StrToWstr(const std::string& source)
{
	return std::wstring().assign(source.begin(), source.end());
}