#include "stdafx.h"
#include "BaseObject.h"


BaseObject::BaseObject()
{
}


BaseObject::~BaseObject()
{
}

void BaseObject::Action()
{
	NextFrame();
}

void BaseObject::draw(CSpriteDib * pSpriteDib, BYTE * bypDest, int iDestWidth, int iDestHeight, int iDestPitch)
{
	pSpriteDib->DrawSprite(m_cur_sprite, _x, _y, bypDest, iDestWidth, iDestHeight, iDestPitch);
}


void BaseObject::SetSprite(int iSpriteStart, int iSpriteMax, int iFrameDelay)
{
	// ��������Ʈ�� ù�κ� ����
	m_iSpriteStart = iSpriteStart;
	m_iSpriteMax = iSpriteMax;
	m_iFrameDelay = iFrameDelay;

	m_cur_sprite = iSpriteStart;
	m_iDelayCount = 0;
	bEndFrame = FALSE;
}

void BaseObject::NextFrame()
{
	// �� ������ Action���� ȣ�����ִ� �Լ�

	if (0 > m_iSpriteStart) {
		return;
	}

	m_iDelayCount++;

	// ������ ���� �ʰ��ϸ� ���� ���������� �Ѿ
	if (m_iDelayCount > m_iFrameDelay) {
		m_iDelayCount = 0;

		m_cur_sprite++;

		// sprite�� ������ �� �� �ִϸ��̼��� �ʰ��ϸ� ó������ ����
		if (m_cur_sprite > m_iSpriteMax) {
			m_cur_sprite = m_iSpriteStart;
			bEndFrame = TRUE;
		}
	}

}