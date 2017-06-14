// SceneManager.cpp

#include "stdafx.h"
#include "SceneManager.h"



SceneManager::SceneManager(HWND * ipHWnd)
{
	pHWnd = ipHWnd;
	pScene = NULL;
	// scene �����͸� title screen�� ����Ű�� ����
	loadScene(_STAGE_TITLE);
}

SceneManager::~SceneManager()
{
	// scene ������ �Ҵ� ����
	delete pScene;
}



void SceneManager::update()
{
	pScene->update();
	checkSceneChange();
}


void SceneManager::checkSceneChange()
{
	// ��ü update �ȿ��� ����ؼ� ���鼭 ���� �����ϴ� scene�� �ٸ� scene���� ������ ��ȣ�� ���´��� �����Ѵ�.
	// ���� flag�� Ȯ���� �Ǿ��ٸ�
	if (pScene->isReadyForNextScene()) {
		// ���� ������ scene�� �����ִ� ������ ���ϴ� ���� scene�� �����Ͽ� scene�� ���� �ҷ��´�.
		loadScene(pScene->getNextScene());
		// flag�� false�� �缳��
		pScene->setReadyToNotReady();
	}

}


void SceneManager::loadScene(STAGE_STATE targetStage)
{
	// ���� pScene ������ �Ҵ� ����
	if (pScene != NULL) {
		delete pScene;
	}

	// ���ڷ� ���� �������� ���¿� ���� �ش� scene ���� �� pScene ������ �Ҵ�
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
