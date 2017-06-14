// SceneManager.h

#pragma once

#include "Scene.h"
#include "TitleScene.h"
#include "InGameScene.h"
#include "GameOverScene.h"

class SceneManager
{
public:
	SceneManager(HWND * ipHWnd);
	virtual ~SceneManager();

	void update();
	void checkSceneChange();
	void loadScene(STAGE_STATE targetStage);



private:
	// ���� �����ϰ��ִ� scene�� ����Ű�� ������
	Scene * pScene;
	HWND * pHWnd;
	

};