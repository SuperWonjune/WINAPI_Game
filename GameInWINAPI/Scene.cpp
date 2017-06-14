// Scene.cpp

#include "stdafx.h"
#include "Scene.h"
#include "InGameScene.h"



Scene::Scene(HWND * ipHWnd) :
	// �Ŵ��� ��ü�� �ʱ�ȭ
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
	// �̷��� §�ٸ� �ܺ�(sceneManager)���� �غ�� ���¸� �غ���� ���� ���·� �����°� �����ϳ� �� �ݴ�� ���� �ʴ´�.
	readyForNextScene = false;
}


STAGE_STATE Scene::getNextScene()
{
	return nextScene;
}


void Scene::setNextSceneAndReady(STAGE_STATE targetScene)
{
	// ���ڷ� �޾ƿ� targetScene�� ���� ���� scene���� �����ϰ�
	// readyForNextScene �÷��׸� true�� ����.

	// �� �Լ��� �� ���Ŀ� SceneManager���� ����� ������ �����ϰ� scene�� �ٲ� ���̴�.

	// protected���� �����Ͽ� �ݵ�� ��ӹ��� scene ���ο����� ���� scene ���濡 �غ�� ���·� �ٲ� �� �ְ� �Ѵ�.
	nextScene = targetScene;
	readyForNextScene = true;
}