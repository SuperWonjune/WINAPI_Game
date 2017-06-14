// GameOverScene.h

#pragma once

#include "Scene.h"

class GameOverScene : public Scene
{
public:
	GameOverScene(HWND * ipHWnd);
	virtual ~GameOverScene();

	void update();
	void getInput();
	void draw();

private:

};