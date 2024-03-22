#pragma once
class Scene;
class SceneMgr
{
	SINGLE(SceneMgr);
public:
	void Init();
	void Update();
	void Render(HDC _dc);
public:
	void LoadScene(const SCENE_TYPE& _scenename);
	void RegisterScene(const SCENE_TYPE& _scenename, std::shared_ptr<Scene> _scene);
	void Release();
public:
	const std::shared_ptr<Scene>& GetCurScene() const
	{
		return m_pCurScene;
	}
	const SCENE_TYPE& GetCurSceneType() const
	{
		return m_curSceneType;
	}
private:
	// ����Ʈ ������
	std::shared_ptr<Scene> m_pCurScene; // ���� ��
	SCENE_TYPE m_curSceneType;
	// ������ �����ϴ� ��.
	map<SCENE_TYPE, std::shared_ptr<Scene>> m_mapScenes;
};