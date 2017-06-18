// BaseObject.h

#pragma once

#include "CSpriteDib.h"
#include "DefineEnum.h"

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void Action();
	virtual void draw(CSpriteDib * pSpriteDib, BYTE * bypDest, int iDestWidth, int iDestHeight, int iDestPitch);

	void SetSprite(int iSpriteStart, int iSpriteMax, int iFrameDelay);
	int GetSprite() { return m_cur_sprite; }
	int isEndFrame() { return bEndFrame; }
	void NextFrame();

	int getX(void) { return _x; }
	int getY(void) { return _y; }

protected:
	// drawing�� SpriteDib ��ü ������ (gameScene���� �޾ƿ´�)
	CSpriteDib  * p_spriteDib;

	// �ִϸ��̼� ó���� ������
	int m_cur_sprite;
	int m_iSpriteStart;
	int m_iSpriteMax;
	int m_iFrameDelay;
	int m_iDelayCount;
	bool bEndFrame;

	// ���� �׼�
	int m_dwActionCur;

	int _x;
	int _y;
};

