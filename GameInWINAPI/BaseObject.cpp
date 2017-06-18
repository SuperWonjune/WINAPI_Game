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
	// 스프라이트의 첫부분 설정
	m_iSpriteStart = iSpriteStart;
	m_iSpriteMax = iSpriteMax;
	m_iFrameDelay = iFrameDelay;

	m_cur_sprite = iSpriteStart;
	m_iDelayCount = 0;
	bEndFrame = FALSE;
}

void BaseObject::NextFrame()
{
	// 매 프레임 Action에서 호출해주는 함수

	if (0 > m_iSpriteStart) {
		return;
	}

	m_iDelayCount++;

	// 딜레이 값을 초과하면 다음 프레임으로 넘어감
	if (m_iDelayCount > m_iFrameDelay) {
		m_iDelayCount = 0;

		m_cur_sprite++;

		// sprite의 프레임 맨 끝 애니메이션을 초과하면 처음으로 돌림
		if (m_cur_sprite > m_iSpriteMax) {
			m_cur_sprite = m_iSpriteStart;
			bEndFrame = TRUE;
		}
	}

}