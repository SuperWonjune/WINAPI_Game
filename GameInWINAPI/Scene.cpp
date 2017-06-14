// Scene.cpp

#include "stdafx.h"
#include "Scene.h"
#include "InGameScene.h"



Scene::Scene(HWND * ipHWnd) :
	// 매니저 객체들 초기화
	g_cScreenDib(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR_BIT), g_cSpriteDib(100, 0x00ffffff), g_frameCheck(FRAME_PER_SECOND)
{
	pHWnd = ipHWnd;
	readyForNextScene = false;
}

Scene::~Scene()
{

}

bool Scene::isReadyForNextScene()
{
	return readyForNextScene;
}

void Scene::setReadyToNotReady()
{
	// 이렇게 짠다면 외부(sceneManager)에서 준비된 상태를 준비되지 않은 상태로 돌리는건 가능하나 그 반대는 되지 않는다.
	readyForNextScene = false;
}


STAGE_STATE Scene::getNextScene()
{
	return nextScene;
}


void Scene::setNextSceneAndReady(STAGE_STATE targetScene)
{
	// 인자로 받아온 targetScene을 다음 변경 scene으로 설정하고
	// readyForNextScene 플래그를 true로 설정.

	// 이 함수를 쓴 직후에 SceneManager에서 변경된 변수를 감지하고 scene을 바꿀 것이다.

	// protected으로 선언하여 반드시 상속받은 scene 내부에서만 다음 scene 변경에 준비된 상태로 바꿀 수 있게 한다.
	nextScene = targetScene;
	readyForNextScene = true;
}