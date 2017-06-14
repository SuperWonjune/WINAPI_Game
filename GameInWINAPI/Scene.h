//Scene.h

#pragma once

// �ڽ� ���
/*
TitleScene
InGameScene
GameOverScene
*/

#include <Windows.h>
#include <iostream>
#include <cstdio>

#include "CScreenDib.h"
#include "CSpriteDib.h"
#include "FrameCheck.h"
#include "DefineEnum.h"

// InGameObjects
#include "BaseObject.h"


// ���� �� �ɼ� ����
#define GAME_WIDTH 640
#define GAME_HEIGHT 480
#define GAME_COLOR_BIT 32
#define FRAME_PER_SECOND 50


// �������� ���� ������
typedef enum
{
	_STAGE_TITLE,
	_STAGE_GAME,
	_STAGE_GAME_OVER
} STAGE_STATE;


class Scene
{
public:
	Scene(HWND * ipHWnd);
	virtual ~Scene();

	virtual void update() = 0;
	virtual void getInput() = 0;

	bool isReadyForNextScene();
	void setReadyToNotReady();
	STAGE_STATE getNextScene();

	// �޾ƿ� ������ �ڵ� ������
	// DC ��¿�
	HWND * pHWnd;

protected:
	// --------------------------------------------
	// �Ŵ��� ��ü��
	// --------------------------------------------
	// �̰� �̱������� �������ϳ�?

	// ȭ�� ��¿� �Ŵ���
	CScreenDib g_cScreenDib;
	CSpriteDib g_cSpriteDib;

	// ������üŷ�� �Ŵ���
	FrameCheck g_frameCheck;


	// ������Ʈ���� ��� ����Ʈ
	std::list<BaseObject> g_ObjectList;



	// --------------------------------------------
	// Scene ��ȯ�� ������
	// --------------------------------------------
	// �ٸ� scene������ ��ȯ ��ȣ flag
	bool readyForNextScene;
	// ��ȯ�� ���� scene�� enum ��ȣ
	STAGE_STATE nextScene;

	// ���ڷ� �޾ƿ� targetScene�� ���� ���� Scene���� �����ϰ�
	// readyForNextScene �÷��׸� true�� ����.
	void setNextSceneAndReady(STAGE_STATE targetScene);
};