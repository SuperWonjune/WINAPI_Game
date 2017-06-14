//Scene.h

#pragma once

// 자식 목록
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


// 게임 내 옵션 세팅
#define GAME_WIDTH 640
#define GAME_HEIGHT 480
#define GAME_COLOR_BIT 32
#define FRAME_PER_SECOND 50


// 스테이지 상태 열거형
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

	// 받아온 윈도우 핸들 포인터
	// DC 출력용
	HWND * pHWnd;

protected:
	// --------------------------------------------
	// 매니저 객체들
	// --------------------------------------------
	// 이걸 싱글턴으로 빼내야하나?

	// 화면 출력용 매니저
	CScreenDib g_cScreenDib;
	CSpriteDib g_cSpriteDib;

	// 프레임체킹용 매니저
	FrameCheck g_frameCheck;


	// 오브젝트들이 담긴 리스트
	std::list<BaseObject> g_ObjectList;



	// --------------------------------------------
	// Scene 전환용 변수들
	// --------------------------------------------
	// 다른 scene으로의 전환 신호 flag
	bool readyForNextScene;
	// 전환할 다음 scene의 enum 번호
	STAGE_STATE nextScene;

	// 인자로 받아온 targetScene을 다음 변경 Scene으로 설정하고
	// readyForNextScene 플래그를 true로 설정.
	void setNextSceneAndReady(STAGE_STATE targetScene);
};