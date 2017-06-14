//TitleScene.cpp

#include "stdafx.h"
#include "TitleScene.h"


TitleScene::TitleScene(HWND * ipHWnd) : Scene(ipHWnd)
{

}

TitleScene::~TitleScene()
{

}



void TitleScene::update()
{
	// 입력
	getInput();

	// 로직
	setNextSceneAndReady(_STAGE_GAME);

	// 출력
	draw();
}

void TitleScene::getInput()
{


}

void TitleScene::draw()
{


}