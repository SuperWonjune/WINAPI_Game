// InGameScene.cpp

#include "stdafx.h"
#include "InGameScene.h"


InGameScene::InGameScene(HWND * ipHWnd) : Scene(ipHWnd)
{
	// ���� �ʱ�ȭ
	InitGame();

	isGameOver = false;
}


InGameScene::~InGameScene()
{
	delete pPlayer;
}

void InGameScene::update()
{
	// �Է�
	getInput();

	// ����
	ObjectListAction();

	// ���
	draw();

}

void InGameScene::getInput()
{
	DWORD dwAction = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8001) dwAction = dfACTION_MOVE_LL;
	if (GetAsyncKeyState(VK_UP) & 0x8001) dwAction = dfACTION_MOVE_UU;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001) dwAction = dfACTION_MOVE_RR;
	if (GetAsyncKeyState(VK_DOWN) & 0x8001) dwAction = dfACTION_MOVE_DD;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8001) && (GetAsyncKeyState(VK_UP) & 0x8001)) dwAction = dfACTION_MOVE_LU;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8001) && (GetAsyncKeyState(VK_UP) & 0x8001)) dwAction = dfACTION_MOVE_RU;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8001) && (GetAsyncKeyState(VK_DOWN) & 0x8001)) dwAction = dfACTION_MOVE_RD;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8001) && (GetAsyncKeyState(VK_DOWN) & 0x8001)) dwAction = dfACTION_MOVE_LD;

	pPlayer->ActionInput(dwAction);
	
}

void InGameScene::draw(void)
{
	BYTE *pDest = g_cScreenDib.GetDibBuffer();
	int iWidth = g_cScreenDib.GetWidth();
	int iHeight = g_cScreenDib.GetHeight();
	int iPitch = g_cScreenDib.GetPitch();

	// map �׸���
	g_cSpriteDib.DrawImage(e_SPRITE::eMAP, 0, 0, pDest, iWidth, iHeight, iPitch);

	// player �׸���
	g_cSpriteDib.DrawSprite(e_SPRITE::ePLAYER_STAND_L01, pPlayer->getX(), pPlayer->getY(), pDest, iWidth, iHeight, iPitch);

	// ���� flip
	g_cScreenDib.DrawBuffer(*pHWnd);
}




BOOL InGameScene::InitGame(void)
{
	// ��������Ʈ �ε�
	if (LoadSprites() == FALSE) return FALSE;


	// �÷��̾� ��ü ���� �� �ʱ� ����
	initPlayer(150, 150);

	return TRUE;
}

BOOL InGameScene::LoadSprites(void)
{
	// ��������Ʈ �ε�

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

	// ��� �ε� ����
	return TRUE;
}

void InGameScene::initPlayer(int xLoc = 0, int yLoc = 0)
{
	// �÷��̾� ��ü ���� �� �Ҵ�
	pPlayer = new Player(xLoc, yLoc);

	// objectList�� ����
	objectList.push_back(pPlayer);

}




void InGameScene::ObjectListAction()
{
	//for (iter = objectList.begin(); iter != objectList.end(); ++iter) (*iter)->Action();
}

void InGameScene::ObjectListDraw()
{
	//for (iter = objectList.begin(); iter != objectList.end(); ++iter) (*iter)->Draw();
}


