#pragma once

#include "resource.h"



// 스테이지 목록
enum GameState {
	Title,
	InGame
};

BOOL InitGame(void);
BOOL LoadSprites(void);
void setToNextStage(GameState &curGameState);
void update(void);
void updateGame(void);
void KeyProcess(void);
void Action(void);
void Draw(void);