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
	// Player ���� �ʱ�ȭ
	void initPlayer(int xLoc, int yLoc);

	// objectList ��ȸ �Լ�
	void ObjectListAction();
	void ObjectListDraw();



	// ���� �� ������ ��� BaseObject�� �Ļ� Ŭ�������� �����Ͱ� ��� ����Ʈ
	list<BaseObject *> objectList;
	// objectList�� ���̴� iterator
	list<BaseObject *>::iterator iter;

	bool isGameOver;

	// �÷��̾� ������
	Player * pPlayer;

};


