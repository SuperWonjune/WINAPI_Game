//TitleScene.h

#pragma once

#include "Scene.h"

// ����� �ƹ� ���� ���� �ٷ� InGameScene���� �Ѿ��.

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