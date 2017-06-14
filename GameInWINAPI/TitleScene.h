//TitleScene.h

#pragma once

#include "Scene.h"

// 현재는 아무 조건 없이 바로 InGameScene으로 넘어간다.

class TitleScene : public Scene
{
public:
	TitleScene(HWND * ipHWnd);
	virtual ~TitleScene();

	void update();
	void getInput();
	void draw();

private:


};