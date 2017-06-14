// SceneManager.cpp

#include "stdafx.h"
#include "SceneManager.h"



SceneManager::SceneManager(HWND * ipHWnd)
{
	pHWnd = ipHWnd;
	pScene = NULL;
	// scene 포인터를 title screen을 가리키게 설정
	loadScene(_STAGE_TITLE);
}

SceneManager::~SceneManager()
{
	// scene 포인터 할당 해제
	delete pScene;
}



void SceneManager::update()
{
	pScene->update();
	checkSceneChange();
}


void SceneManager::checkSceneChange()
{
	// 자체 update 안에서 계속해서 돌면서 현재 참조하는 scene이 다른 scene으로 변경할 신호를 보냈는지 감지한다.
	// 만약 flag가 확인이 되었다면
	if (pScene->isReadyForNextScene()) {
		// 현재 참조된 scene이 갖고있는 변경을 원하는 다음 scene을 참조하여 scene을 새로 불러온다.
		loadScene(pScene->getNextScene());
		// flag를 false로 재설정
		pScene->setReadyToNotReady();
	}

}


void SceneManager::loadScene(STAGE_STATE targetStage)
{
	// 기존 pScene 포인터 할당 해제
	if (pScene != NULL) {
		delete pScene;
	}

	// 인자로 들어온 스테이지 상태에 따라 해당 scene 생성 후 pScene 포인터 할당
	switch (targetStage)
	{
	case _STAGE_TITLE:
		pScene = new TitleScene(pHWnd);
		break;
	case _STAGE_GAME:
		pScene = new InGameScene(pHWnd);
		break;

	case _STAGE_GAME_OVER:
		pScene = new GameOverScene(pHWnd);
		break;

	default:
		break;
	}

}
