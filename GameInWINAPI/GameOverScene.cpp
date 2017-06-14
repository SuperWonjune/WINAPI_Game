// GameOverScene.cpp

#include "stdafx.h"
#include "GameOverScene.h"



GameOverScene::GameOverScene(HWND * ipHWnd) : Scene(ipHWnd)
{

}

GameOverScene::~GameOverScene()
{

}


void GameOverScene::update()
{
	// ÀÔ·Â
	getInput();

	// ·»´õ¸µ
	draw();
}

void GameOverScene::getInput()
{
	/*
	// 0x53 == s
	if (GetAsyncKeyState(0x53) & 0x0001) {
		setNextSceneAndReady(_STAGE_GAME);
	}
	*/
}

void GameOverScene::draw()
{

}
