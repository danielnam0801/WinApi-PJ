#include "pch.h"
#include "MapMgr.h"
#include "MapObject.h"
#include "ShellObject.h"
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
#include "ShellObject.h"


void MapMgr::Init()
{
	//BackGroundLayer
	//ObjectLayer
	//std::cout << fs::absolute(fs::path("./"));
	
	m_uptrMap = m_tson.parse(fs::path("./Map/FinalJumpMap (1).json"));
	if (m_uptrMap->getStatus() != tson::ParseStatus::OK)
	{
		std::cout << "json file error " << std::endl;
	}
}

void MapMgr::CreateJsonBoard()
{
	Vec2  m_Scale = { 2.f, 2.f };
	if (m_uptrMap->getStatus() == tson::ParseStatus::OK)
	{
		
		//tson::Layer* bgLayer = m_uptrMap->getLayer("BackGroundLayer");
		tson::Layer* ShellLayer = m_uptrMap->getLayer("ShellObjectLayer");
		tson::Layer* objLayer = m_uptrMap->getLayer("ObjectLayer");
		tson::Layer* startPointLayer = m_uptrMap->getLayer("StartPoint");
		tson::Layer* endPointLayer = m_uptrMap->getLayer("EndPoint");
		
		if (startPointLayer->getType() == tson::LayerType::ObjectGroup)
		{
			tson::Object* spawn = startPointLayer->firstObj("StartPoint");
			//Vec2 origin = { (float)spawn->getSize().x / 2.f, (float)spawn->getSize().y / 2.f};
			//origin *= m_Scale;
			//spawnPoint = Vec2{ (spawn->getPosition().x + origin.x) * m_Scale.x, (spawn->getPosition().y + origin.y) * m_Scale.y };
			spawnPoint = Vec2{ spawn->getPosition().x, spawn->getPosition().y };
		}
		if (endPointLayer->getType() == tson::LayerType::ObjectGroup)
		{
			tson::Object* spawn = endPointLayer->firstObj("EndPoint");
			//endPoint = Vec2{ spawn->getPosition().x * m_Scale.x, spawn->getPosition().y * m_Scale.y};
			endPoint = Vec2{ spawn->getPosition().x, spawn->getPosition().y};
		}


		for (auto& obj : ShellLayer->getObjects())
		{
			tson::Vector2i position = obj.getPosition();
			tson::Vector2i size = obj.getSize();
			
			ShellObject* shellObj = new ShellObject;
			//shellObj->SetPos(Vec2{ (position.x + origin.x) * m_Scale.x, (position.y + origin.y) * m_Scale.y});
			shellObj->SetPos(Vec2{ position.x, position.y });
			m_shellObjs.push_back(shellObj);
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
		
			MapObject* image = StoreAndLoadImageMapObject(path, { 0, 0 });
			MapObject* sprite = new MapObject;
			sprite->DeepCopy(image);

			sprite->SetTextureRect({ rect.x, rect.y, rect.width , rect.height });

			sprite->SetScale(m_Scale);
			sprite->SetName(L"Ground");
			////	// origin 세팅

			Vec2 origin = { (float)rect.width / 2.f, (float)rect.height / 2.f };
			//Vec2 origin = { 0.f, 0.f };
			origin *= m_Scale;
			sprite->GetCollider()->SetOffSetPos(origin);
			
			////	// position 세팅
			realPos = { (realPos.x + origin.x) * m_Scale.x , (realPos.y + origin.y) * m_Scale.y };
			sprite->SetPos({ realPos.x, realPos.y });
				
			////	// collider 세팅
			Vec2 size = Vec2((float)rect.width, (float)rect.height);
			size *= m_Scale;
			sprite->GetCollider()->SetScale(size);

			m_mapObjs.push_back(sprite);

		}
	}
}

MapObject* MapMgr::StoreAndLoadImageMapObject(const std::string& _image, const Vec2 _pos)
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


//ShellObject* MapMgr::StoreAndLoadImageShellObject(const std::string& _image, const Vec2 _pos)
//{
//	fs::path path = _image;
//	if (m_maptex.count(_image) == 0)
//	{
//		//if (fs::exists(path) && fs::is_regular_file(path))
//
//		std::shared_ptr<Texture> tex = ResMgr::GetInst()->TexLoad(StrToWstr(_image), path);
//		//bool imageFound = tex->LoadFromFile(tex->GetRelativePath());
//		if (tex != nullptr)
//		{
//			ShellObject* spr = new ShellObject;
//			spr->SetTexture(tex);
//			m_maptex[_image] = tex;
//			m_shellsprite[_image] = spr;
//		}
//		else
//		{
//			std::cout << "can't find" << path.generic_string() << std::endl;
//		}
//	}
//	if (m_shellsprite.count(_image) > 0)
//		return m_shellsprite[_image];
//	return nullptr;
//}

std::string MapMgr::WstrToStr(const std::wstring& source)
{
	return std::string().assign(source.begin(), source.end());
}

std::wstring MapMgr::StrToWstr(const std::string& source)
{
	return std::wstring().assign(source.begin(), source.end());
}