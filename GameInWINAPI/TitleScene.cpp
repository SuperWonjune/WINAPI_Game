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
	// �Է�
	getInput();

	// ����
	setNextSceneAndReady(_STAGE_GAME);

	// ���
	draw();
}

void TitleScene::getInput()
{


}

void TitleScene::draw()
{


}