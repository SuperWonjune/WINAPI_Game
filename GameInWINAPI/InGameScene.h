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
	void KeyProcess();
	void Action();
	void draw();

private:
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


