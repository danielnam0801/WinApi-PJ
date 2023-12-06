#pragma once
class Camera;
class CameraMgr
{
	SINGLE(CameraMgr);
public:
	void Init();
	void Update();
	void Render(HDC _dc);
public:
	void ChangeCamera();
private:
	//vector<Camera*> cams;
	Camera* _mainCam;
};

