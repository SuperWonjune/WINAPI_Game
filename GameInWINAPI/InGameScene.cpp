// InGameScene.cpp

#include "stdafx.h"
#include "InGameScene.h"


InGameScene::InGameScene(HWND * ipHWnd)
	: Scene(ipHWnd),

	  
	// FrameCheck 초기화
	  frame_check(FRAME_RATE, ipHWnd)
{
	// 게임 초기화
	
	InitGame(),
	isGameOver = false;
}


InGameScene::~InGameScene()
{
	delete pPlayer;
}

void InGameScene::update()
{
	// 입력
	KeyProcess();

	// 로직
	Action();


	// 프레임 스킵할 상황이 아닐 경우
	if (frame_check.checkFrame()) {
		// 출력
		draw();
	}

}

void InGameScene::KeyProcess()
{
	// 기본값으로 STAND를 주는게 맞는건가?
	// 문제점 : 매 프레임마다 호출되는 함수이므로 공격 같은 동작이 아직 끝나지 않았는데도 ActionInput엔 STAND 값이 들어간다.
	DWORD dwAction = dfACTION_STAND;

	if (GetAsyncKeyState(VK_LEFT) & 0x8001) dwAction = dfACTION_MOVE_LL;
	if (GetAsyncKeyState(VK_UP) & 0x8001) dwAction = dfACTION_MOVE_UU;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001) dwAction = dfACTION_MOVE_RR;
	if (GetAsyncKeyState(VK_DOWN) & 0x8001) dwAction = dfACTION_MOVE_DD;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8001) && (GetAsyncKeyState(VK_UP) & 0x8001)) dwAction = dfACTION_MOVE_LU;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8001) && (GetAsyncKeyState(VK_UP) & 0x8001)) dwAction = dfACTION_MOVE_RU;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8001) && (GetAsyncKeyState(VK_DOWN) & 0x8001)) dwAction = dfACTION_MOVE_RD;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8001) && (GetAsyncKeyState(VK_DOWN) & 0x8001)) dwAction = dfACTION_MOVE_LD;

	// Z키
	if (GetAsyncKeyState(0x5A) & 0x8001) dwAction = dfACTION_ATTACK1;
	// X키
	if (GetAsyncKeyState(0x58) & 0x0001) dwAction = dfACTION_ATTACK2;
	// C키
	if (GetAsyncKeyState(0x43) & 0x0001) dwAction = dfACTION_ATTACK3;


	pPlayer->ActionInput(dwAction);
}

void InGameScene::draw()
{
	BYTE *pDest = g_cScreenDib.GetDibBuffer();
	int iWidth = g_cScreenDib.GetWidth();
	int iHeight = g_cScreenDib.GetHeight();
	int iPitch = g_cScreenDib.GetPitch();

	// map 그리기
	g_cSpriteDib.DrawImage(e_SPRITE::eMAP, 0, 0, pDest, iWidth, iHeight, iPitch);

	// 리스트 순환하면서 각 객체들 draw
	for (iter = objectList.begin(); iter != objectList.end(); ++iter) {
		(*iter)->draw(&g_cSpriteDib, pDest, iWidth, iHeight, iPitch);
	}
	
	// 버퍼 flip
	g_cScreenDib.DrawBuffer(*pHWnd);

	// fps 출력
	HDC hdc = GetDC(*pHWnd);
	TCHAR str2[128];
	int cur_time = timeGetTime();
	if ((cur_time - prevTime) != 0) {
		wsprintf(str2, L"%d", 1000 / (cur_time - prevTime));
		TextOut(hdc, 0, 0, str2, wcslen(str2));
	}
	prevTime = timeGetTime();

	ReleaseDC(*pHWnd, hdc);
}


void InGameScene::Action()
{
	for (iter = objectList.begin(); iter != objectList.end(); ++iter) (*iter)->Action();

	// y좌표 기준으로 정렬, 이펙트 종류는 제일 뒤로 정렬

}





BOOL InGameScene::InitGame(void)
{
	// 스프라이트 로딩
	if (LoadSprites() == FALSE) return FALSE;


	// 플레이어 객체 생성 및 초기 설정
	initPlayer(300, 200);

	return TRUE;
}

BOOL InGameScene::LoadSprites(void)
{
	// 스프라이트 로딩

	// STANDING_LEFT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::eMAP, L"\SpriteData\\_Map.bmp", 0, 0))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_L01, L"\SpriteData\\Stand_L_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_L02, L"\SpriteData\\Stand_L_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_L03, L"\SpriteData\\Stand_L_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_L04, L"\SpriteData\\Stand_L_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_L05, L"\SpriteData\\Stand_L_01.bmp", 71, 90))
		return FALSE;

	// STANDING_RIGHT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_R01, L"\SpriteData\\Stand_R_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_R02, L"\SpriteData\\Stand_R_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_R03, L"\SpriteData\\Stand_R_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_R04, L"\SpriteData\\Stand_R_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_STAND_R05, L"\SpriteData\\Stand_R_01.bmp", 71, 90))
		return FALSE;

	// MOVING_LEFT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L01, L"\SpriteData\\Move_L_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L02, L"\SpriteData\\Move_L_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L03, L"\SpriteData\\Move_L_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L04, L"\SpriteData\\Move_L_04.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L05, L"\SpriteData\\Move_L_05.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L06, L"\SpriteData\\Move_L_06.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L07, L"\SpriteData\\Move_L_07.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L08, L"\SpriteData\\Move_L_08.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L09, L"\SpriteData\\Move_L_09.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L10, L"\SpriteData\\Move_L_10.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L11, L"\SpriteData\\Move_L_11.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_L12, L"\SpriteData\\Move_L_12.bmp", 71, 90))
		return FALSE;


	//MOVING_RIGHT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R01, L"\SpriteData\\Move_R_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R02, L"\SpriteData\\Move_R_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R03, L"\SpriteData\\Move_R_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R04, L"\SpriteData\\Move_R_04.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R05, L"\SpriteData\\Move_R_05.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R06, L"\SpriteData\\Move_R_06.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R07, L"\SpriteData\\Move_R_07.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R08, L"\SpriteData\\Move_R_08.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R09, L"\SpriteData\\Move_R_09.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R10, L"\SpriteData\\Move_R_10.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R11, L"\SpriteData\\Move_R_11.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_MOVE_R12, L"\SpriteData\\Move_R_12.bmp", 71, 90))
		return FALSE;

	//ATTACKING1_LEFT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK1_L01, L"\SpriteData\\Attack1_L_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK1_L02, L"\SpriteData\\Attack1_L_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK1_L03, L"\SpriteData\\Attack1_L_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK1_L04, L"\SpriteData\\Attack1_L_04.bmp", 71, 90))
		return FALSE;

	//ATTACKING1_RIGHT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK1_R01, L"\SpriteData\\Attack1_R_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK1_R02, L"\SpriteData\\Attack1_R_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK1_R03, L"\SpriteData\\Attack1_R_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK1_R04, L"\SpriteData\\Attack1_R_04.bmp", 71, 90))
		return FALSE;

	//ATTACKING2_LEFT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK2_L01, L"\SpriteData\\Attack2_L_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK2_L02, L"\SpriteData\\Attack2_L_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK2_L03, L"\SpriteData\\Attack2_L_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK2_L04, L"\SpriteData\\Attack2_L_04.bmp", 71, 90))
		return FALSE;

	//ATTACKING2_RIGHT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK2_R01, L"\SpriteData\\Attack2_R_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK2_R02, L"\SpriteData\\Attack2_R_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK2_R03, L"\SpriteData\\Attack2_R_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK2_R04, L"\SpriteData\\Attack2_R_04.bmp", 71, 90))
		return FALSE;


	//ATTACKING3_LEFT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_L01, L"\SpriteData\\Attack3_L_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_L02, L"\SpriteData\\Attack3_L_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_L03, L"\SpriteData\\Attack3_L_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_L04, L"\SpriteData\\Attack3_L_04.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_L05, L"\SpriteData\\Attack3_L_05.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_L06, L"\SpriteData\\Attack3_L_06.bmp", 71, 90))
		return FALSE;

	//ATTACKING3_RIGHT
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_R01, L"\SpriteData\\Attack3_R_01.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_R02, L"\SpriteData\\Attack3_R_02.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_R03, L"\SpriteData\\Attack3_R_03.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_R04, L"\SpriteData\\Attack3_R_04.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_R05, L"\SpriteData\\Attack3_R_05.bmp", 71, 90))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::ePLAYER_ATTACK3_R06, L"\SpriteData\\Attack3_R_06.bmp", 71, 90))
		return FALSE;

	//EFFECT_SPARK
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::eEFFECT_SPARK_01, L"\SpriteData\\xSpark_1.bmp", 70, 70))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::eEFFECT_SPARK_02, L"\SpriteData\\xSpark_2.bmp", 70, 70))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::eEFFECT_SPARK_03, L"\SpriteData\\xSpark_3.bmp", 70, 70))
		return FALSE;
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::eEFFECT_SPARK_04, L"\SpriteData\\xSpark_4.bmp", 70, 70))
		return FALSE;

	//HP_GUAGE
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::eGUAGE_HP, L"\SpriteData\\HPGuage.bmp", 0, 0))
		return FALSE;

	//SHADOW
	if (!g_cSpriteDib.LoadDibSprite(e_SPRITE::eSHADOW, L"\SpriteData\\Shadow.bmp", 32, 4))
		return FALSE;


	// END_LOADING

	// 모두 로딩 성공
	return TRUE;
}

void InGameScene::initPlayer(int xLoc, int yLoc)
{
	// 플레이어 객체 생성 및 할당
	pPlayer = new Player(xLoc, yLoc);

	// objectList에 삽입
	objectList.push_back(pPlayer);

}




