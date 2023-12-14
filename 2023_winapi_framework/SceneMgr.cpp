#include "pch.h"
#include "SceneMgr.h"
#include "Start_Scene.h"
#include "Game_Scene.h"
void SceneMgr::Init()
{
	m_pCurScene = nullptr;
	// ¾À µî·Ï
	RegisterScene(SCENE_TYPE::START_SCENE,std::make_shared<Start_Scene>());
	RegisterScene(SCENE_TYPE::GAME_SCENE, std::make_shared<Game_Scene>());

	// Ã¹ ¾À ÁöÁ¤
	LoadScene(SCENE_TYPE::START_SCENE);
	m_curSceneType = SCENE_TYPE::START_SCENE;
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}

void SceneMgr::LoadScene(const SCENE_TYPE& _scenename)
{
	// ¾ÀÀÌ ÀÖÀ¸¸é

	m_curSceneType = _scenename;
	if (m_pCurScene != nullptr)
	{
		m_pCurScene->Release();
		m_pCurScene = nullptr;
	}

	auto iter = m_mapScenes.find(_scenename);
	if (iter != m_mapScenes.end())
	{
		m_pCurScene = iter->second;
		m_pCurScene->Init();
	}
}

void SceneMgr::RegisterScene(const SCENE_TYPE& _scenename, std::shared_ptr<Scene> _scene)
{
	m_mapScenes.insert(m_mapScenes.end(), {_scenename, _scene});
}
