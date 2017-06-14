// Game.h

#pragma once

#include "SceneManager.h"

/*
매니저 분포도

Game
↓
SceneManager
↓
각 scene들
↓
ScreenDib, SpriteDib, FrameCheck

*/

// scene에서 API에 접근해서 그릴려면 핸들이 필요한데
// 이렇게 핸들 포인터를 생성자 매개변수로 밑으로 쭉쭉 전달시키는 방법 밖에 없는건가..

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

