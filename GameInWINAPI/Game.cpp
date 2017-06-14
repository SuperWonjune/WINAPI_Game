// Game.cpp

#include "stdafx.h"
#include "Game.h"


Game::Game(HWND *ipHWnd)
{
	// �� sceneManager ���� �Ҵ�
	pSceneManager = new SceneManager(ipHWnd);
}


Game::~Game()
{
	// sceneManager ���� �Ҵ� ����
	delete pSceneManager;
}

void Game::update(void)
{
	pSceneManager->update();
	Sleep(20);
}


