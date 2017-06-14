// Game.h

#pragma once

#include "SceneManager.h"

/*
�Ŵ��� ������

Game
��
SceneManager
��
�� scene��
��
ScreenDib, SpriteDib, FrameCheck

*/

// scene���� API�� �����ؼ� �׸����� �ڵ��� �ʿ��ѵ�
// �̷��� �ڵ� �����͸� ������ �Ű������� ������ ���� ���޽�Ű�� ��� �ۿ� ���°ǰ�..

class Game
{
public:
	Game(HWND * ipHWnd);
	virtual ~Game();

	void update(void);

private:
	SceneManager *pSceneManager;
	HWND * pHWnd;
};

