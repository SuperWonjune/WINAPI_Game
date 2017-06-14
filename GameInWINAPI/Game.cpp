// Game.cpp

#include "stdafx.h"
#include "Game.h"


Game::Game(HWND *ipHWnd)
{
	// 새 sceneManager 동적 할당
	pSceneManager = new SceneManager(ipHWnd);
}


Game::~Game()
{
	// sceneManager 동적 할당 해제
	delete pSceneManager;
}

void Game::update(void)
{
	pSceneManager->update();
	Sleep(20);
}


