// Player.cpp

#include "stdafx.h"
#include "Player.h"

#define dfRANGE_MOVE_TOP	50
#define dfRANGE_MOVE_LEFT	10
#define dfRANGE_MOVE_RIGHT	630
#define dfRANGE_MOVE_BOTTOM	470


Player::Player(int x, int y)
{
	m_dwActionCur = dfACTION_STAND;
	_x = x;
	_y = y;
	_HP = 100;

	_player_X_Speed = 2;
	_player_Y_Speed = 2;

	// 우측 바라보게 설정
	m_iDirCur = 1;
	_attacking = false;
	// 가만히 서있자
	SetActionStand();
}


Player::~Player()
{
}

void Player::Action()
{
	NextFrame();
	ActionProc();
}

void Player::ActionInput(DWORD dwAction)
{
	// 외부에서로부터 입력된 액션 변수 세팅만 해줌.
	m_dwActionOld = m_dwActionCur;
	m_dwActionCur = dwAction;
}

void Player::ActionProc()
{
	// 강제적으로 동작 처리 완료
	// 애니메이션이 끝난후 기본동작으로 복귀

	// 아직 공격 중일 경우
	if (_attacking) {
		m_dwActionCur = dfACTION_ATTACK1;
		if (isEndFrame()) {
			m_dwActionOld = m_dwActionCur;
			m_dwActionCur = dfACTION_STAND;
			_attacking = false;
			SetActionStand();
		}
	}

	else {
		InputActionProc();
	}

	
	// 이 구조로 가면 맨 처음 공격 키를 눌렀을때도 바로 case 분기문으로 들어가서 InputActionProc()이 애초에 호출이 안되는데..?
	/*
		switch (m_dwActionCur)
	{
		case dfACTION_ATTACK1:
		case dfACTION_ATTACK2:
		case dfACTION_ATTACK3:
			if (isEndFrame()) {
				
			}
			break;
	default:
		// 액션 처리
		
		break;
	}
	*/
	

}

void Player::InputActionProc()
{
	switch (m_dwActionCur) {

		// 아무키도 눌러지지 않았을 때

	case dfACTION_STAND:
		SetActionStand();
		break;

	case dfACTION_MOVE_LL:
		if (_x <= dfRANGE_MOVE_LEFT) break;
		_x -= _player_X_Speed;
		m_iDirCur = 0;

		SetActionMove();
		break;
	case dfACTION_MOVE_LU:
		if (_x <= dfRANGE_MOVE_LEFT || _y <= dfRANGE_MOVE_TOP) break;
		_x -= _player_X_Speed;
		_y -= _player_Y_Speed;
		m_iDirCur = 0;

		SetActionMove();
		break;
	case dfACTION_MOVE_UU:
		if (_y <= dfRANGE_MOVE_TOP) break;
		_y -= _player_Y_Speed;

		SetActionMove();
		break;
	case dfACTION_MOVE_RU:
		if (_x >= dfRANGE_MOVE_RIGHT || _y <= dfRANGE_MOVE_TOP) break;
		_x += _player_X_Speed;
		_y -= _player_Y_Speed;
		m_iDirCur = 1;

		SetActionMove();
		break;
	case dfACTION_MOVE_RR:
		if (_x >= dfRANGE_MOVE_RIGHT) break;
		_x += _player_X_Speed;
		m_iDirCur = 1;

		SetActionMove();
		break;
	case dfACTION_MOVE_RD:
		if (_x >= dfRANGE_MOVE_RIGHT || _y >= dfRANGE_MOVE_BOTTOM) break;
		_x += _player_X_Speed;
		_y += _player_Y_Speed;
		m_iDirCur = 1;

		SetActionMove();
		break;
	case dfACTION_MOVE_DD:
		if (_y >= dfRANGE_MOVE_BOTTOM) break;
		_y += _player_X_Speed;

		SetActionMove();
		break;
	case dfACTION_MOVE_LD:
		if (_x <= dfRANGE_MOVE_LEFT || _y >= dfRANGE_MOVE_BOTTOM) break;
		_x -= _player_X_Speed;
		_y += _player_Y_Speed;
		m_iDirCur = 0;

		SetActionMove();
		break;
	case dfACTION_ATTACK1:
		SetActionAttack1();
		break;
	case dfACTION_ATTACK2:
		SetActionAttack2();
		break;
	case dfACTION_ATTACK3:
		SetActionAttack3();
		break;
			
	default:
		break;
	}

}

void Player::draw(CSpriteDib * pSpriteDib, BYTE * bypDest, int iDestWidth, int iDestHeight, int iDestPitch)
{
	// 그림자 출력
	pSpriteDib->DrawSprite(eSHADOW, _x, _y, bypDest, iDestWidth, iDestHeight, iDestPitch);

	// 플레이어 출력
	pSpriteDib->DrawSprite(m_cur_sprite, _x, _y, bypDest, iDestWidth, iDestHeight, iDestPitch);

	// HP 출력
	pSpriteDib->DrawSprite(eGUAGE_HP, _x - 35 , _y + 9, bypDest, iDestWidth, iDestHeight, iDestPitch,_HP);
}

void Player::SetActionStand()
{
	// 액션이 바뀌었을 때만 감지.
	if (m_dwActionCur != m_dwActionOld) {
		// 왼쪽 바라볼 때
		if (m_iDirCur == 0) {
			SetSprite(ePLAYER_STAND_L01, ePLAYER_STAND_L_MAX, dfDELAY_STAND);
		}

		// 오른쪽 바라볼 때
		else if (m_iDirCur == 1) {
			SetSprite(ePLAYER_STAND_R01, ePLAYER_STAND_R_MAX, dfDELAY_STAND);
		}
	}
}

void Player::SetActionMove()
{
	// 액션이 바뀌었을 때만 감지.
	if (m_dwActionCur != m_dwActionOld) {
		// 왼쪽 바라볼 때
		if (m_iDirCur == 0) {
			SetSprite(ePLAYER_MOVE_L01, ePLAYER_MOVE_L_MAX, dfDELAY_MOVE);
		}

		// 오른쪽 바라볼 때
		else if (m_iDirCur == 1) {
			SetSprite(ePLAYER_MOVE_R01, ePLAYER_MOVE_R_MAX, dfDELAY_MOVE);
		}

	}

}

void Player::SetActionAttack1()
{
	_attacking = true;
	// 왼쪽 바라볼 때
	if (m_iDirCur == 0) {
		SetSprite(ePLAYER_ATTACK1_L01, ePLAYER_ATTACK1_L_MAX, dfDELAY_ATTACK1);
	}

	// 오른쪽 바라볼 때
	else if (m_iDirCur == 1) {
		SetSprite(ePLAYER_ATTACK1_R01, ePLAYER_ATTACK1_R_MAX, dfDELAY_ATTACK1);
	}

}

void Player::SetActionAttack2()
{
	_attacking = true;

	// 왼쪽 바라볼 때
	if (m_iDirCur == 0) {
		SetSprite(ePLAYER_ATTACK2_L01, ePLAYER_ATTACK2_L_MAX, dfDELAY_ATTACK2);
	}

	// 오른쪽 바라볼 때
	else if (m_iDirCur == 1) {
		SetSprite(ePLAYER_ATTACK2_R01, ePLAYER_ATTACK2_R_MAX, dfDELAY_ATTACK2);
	}

}

void Player::SetActionAttack3()
{
	_attacking = true;

	// 왼쪽 바라볼 때
	if (m_iDirCur == 0) {
		SetSprite(ePLAYER_ATTACK3_L01, ePLAYER_ATTACK3_L_MAX, dfDELAY_ATTACK3);
	}

	// 오른쪽 바라볼 때
	else if (m_iDirCur == 1) {
		SetSprite(ePLAYER_ATTACK3_R01, ePLAYER_ATTACK3_R_MAX, dfDELAY_ATTACK3);
	}
}



bool Player::CheckOutOfBoundary()
{
	if (_x <= dfRANGE_MOVE_LEFT || _x >= dfRANGE_MOVE_RIGHT || _y <= dfRANGE_MOVE_TOP || _y >= dfRANGE_MOVE_BOTTOM) {
		return true;
	}
	else return false;
}