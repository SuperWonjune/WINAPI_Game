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
	// 현재 실행하고있는 scene을 가리키는 포인터
	Scene * pScene;
	HWND * pHWnd;
	

};