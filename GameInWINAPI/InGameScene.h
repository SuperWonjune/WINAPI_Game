// InGameScene.h

#pragma once

#include "Scene.h"
#include "Player.h"
#include "FrameCheck.h"

#include <list>

#define FRAME_RATE 50

using namespace std;

class InGameScene : public Scene
{
public:
	InGameScene(HWND * ipHWnd);
	virtual ~InGameScene();

	void update();
	void KeyProcess();
	void Action();
	void draw();

private:
	FrameCheck frame_check;
	DWORD prevTime;
	DWORD cur_time;

	BOOL InitGame(void);
	BOOL LoadSprites(void);
	// Player ���� �ʱ�ȭ
	void initPlayer(int xLoc, int yLoc);

	// ���� �� ������ ��� BaseObject�� �Ļ� Ŭ�������� �����Ͱ� ��� ����Ʈ
	list<BaseObject *> objectList;
	// objectList�� ���̴� iterator
	list<BaseObject *>::iterator iter;

	bool isGameOver;

	// �÷��̾� ������
	Player * pPlayer;
};


