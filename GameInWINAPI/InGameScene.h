// InGameScene.h

#pragma once

#include "Scene.h"
#include "Player.h"

#include <list>
using namespace std;


class InGameScene : public Scene
{
public:
	InGameScene(HWND * ipHWnd);
	virtual ~InGameScene();

	void update();
	void getInput();
	void draw(void);

private:
	BOOL InitGame(void);
	BOOL LoadSprites(void);
	// Player 관련 초기화
	void initPlayer(int xLoc, int yLoc);

	// objectList 순회 함수
	void ObjectListAction();
	void ObjectListDraw();



	// 게임 내 구현된 모든 BaseObject의 파생 클래스들의 포인터가 담긴 리스트
	list<BaseObject *> objectList;
	// objectList에 쓰이는 iterator
	list<BaseObject *>::iterator iter;

	bool isGameOver;

	// 플레이어 포인터
	Player * pPlayer;

};


