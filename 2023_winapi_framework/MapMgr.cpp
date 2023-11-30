#include "pch.h"
#include "MapMgr.h"
#include "MapObject.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include <tileson.hpp>
#include "tests/tson_files.h"

void MapMgr::Init()
{
    tson::Tileson t;
    std::unique_ptr<tson::Map> map = t.parse(fs::path("./path/to/map.json"));

    if (map->getStatus() == tson::ParseStatus::OK)
    {
        //Gets the layer called "Object Layer" from the "ultimate_demo.json map
        tson::Layer* objectLayer = map->getLayer("Object Layer"); //This is an Object Layer

        //Example from an Object Layer.
        if (objectLayer->getType() == tson::LayerType::ObjectGroup)
        {
            tson::Object* goomba = objectLayer->firstObj("goomba"); //Gets the first object with this name. This can be any object.

            //If you want to just go through every existing object in the layer:
            for (auto& obj : objectLayer->getObjects())
            {
                tson::Vector2i position = obj.getPosition();
                tson::Vector2i size = obj.getSize();
                tson::ObjectType objType = obj.getObjectType();

                //You may want to check the object type to make sure you use the data right.
            }

            tson::ObjectType objType = goomba->getObjectType();

            /*!
             * tson::ObjectType is defined like this.
             * They are automatically detected based on what kind of object you have created
             * enum class Type : uint8_t
                {
                    Undefined = 0,
                    Object = 1,
                    Ellipse = 2, //<-- Circle
                    Rectangle = 3,
                    Point = 4,
                    Polygon = 5,
                    Polyline = 6,
                    Text = 7,
                    Template = 8
                };
             */

            if (objType == tson::ObjectType::Rectangle)
            {
                tson::Vector2i size = goomba->getSize();
                tson::Vector2i position = goomba->getPosition();

                //If you have set a custom property, you can also get this
                int hp = goomba->get<int>("hp");

                //Using size and position you can can create a Rectangle object by your library of choice.
                //An example if you were about to use SFML for drawing:
                //sf::RectangleShape rect;
                //rect.setSize(sf::Vector2f(size.x, size.y));
                //rect.setPosition(sf::Vector2f(position.x, position.y));
            }
            else if (objType == tson::ObjectType::Polygon)
            {
                for (auto const& poly : goomba->getPolygons())
                {
                    //Set a point on a shape taking polygons
                }
                tson::Vector2i position = goomba->getPosition();
            }
            else if (objType == tson::ObjectType::Polyline)
            {
                std::vector<tson::Vector2i> polys = goomba->getPolylines();
                for (auto const& poly : goomba->getPolylines())
                {

                }
                tson::Vector2i position = goomba->getPosition();
            }
        }

        tson::Layer* tileLayer = map->getLayer("Main Layer"); //This is a Tile Layer.

        //You can get your tileset like this, but in v1.2.0
        //The tiles themselves holds a pointer to their related tileset.
        tson::Tileset* tileset = map->getTileset("demo-tileset");

        //Example from a Tile Layer
        //I know for a fact that this is a Tile Layer, but you can check it this way to be sure.
        if (tileLayer->getType() == tson::LayerType::TileLayer)
        {
            //pos = position in tile units
            for (auto& [pos, tileObject] : tileLayer->getTileObjects()) //Loops through absolutely all existing tileObjects
            {
                tson::Tileset* tileset = tileObject.getTile()->getTileset();
                tson::Rect drawingRect = tileObject.getDrawingRect();
                tson::Vector2f position = tileObject.getPosition();

                //Here you can determine the offset that should be set on a sprite
                //Example on how it would be done using SFML (where sprite presumably is a member of a generated game object):
                //sf::Sprite *sprite = storeAndLoadImage(tileset->getImage().u8string(), {0, 0});
                //if (sprite != nullptr)
                //{
                //    sprite->setTextureRect({drawingRect.x, drawingRect.y, drawingRect.width, drawingRect.height});
                //    sprite->setPosition({position.x, position.y});
                //    m_window.draw(*sprite);
                //}
            }
        }
    }

}

void MapMgr::MakeObject(MAPOBJECT_TYPE _type)
{
	//MapObject* obj = new MapObject(_type);
	//obj->SetPos(Vec2{ WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 });
	//m_mapObjs.push_back(obj);
}

void MapMgr::MovingObject()
{
	if (m_currentSelectObj == NULL) return;
	m_currentSelectObj->SetPos(m_mouseObj->GetPos());
}

void MapMgr::ReleaseObject()
{
	m_currentSelectObj->SetIsClicked(false);
	m_currentSelectObj = NULL;
}

//void MapMgr::SaveObjectInfo(int idx)
//{
//
//}

void MapMgr::LoadObjectInfo()
{
}

Object* MapMgr::FindObject(Vec2 m_mousePos)
{
	for (int i = 0; i < m_mapObjs.size(); i++)
	{
		if (CollisionMgr::GetInst()->CheckContainObject(m_mousePos, m_mapObjs[i]->GetCollider()))
		{
			return m_mapObjs[i];
		}
	}
	return NULL;
}

void MapMgr::Update()
{
	m_mouseObj->SetPos(KeyMgr::GetInst()->GetMousePos());
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
	MovingObject();
}

void MapMgr::Render(HDC _dc)
{
	for (auto& object : m_mapObjs)
	{
		object->Render(_dc);
	}
}
