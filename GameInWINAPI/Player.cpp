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

	// ���� �ٶ󺸰� ����
	m_iDirCur = 1;
	_attacking = false;
	// ������ ������
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
	// �ܺο����κ��� �Էµ� �׼� ���� ���ø� ����.
	m_dwActionOld = m_dwActionCur;
	m_dwActionCur = dwAction;
}

void Player::ActionProc()
{
	// ���������� ���� ó�� �Ϸ�
	// �ִϸ��̼��� ������ �⺻�������� ����

	// ���� ���� ���� ���
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

	
	// �� ������ ���� �� ó�� ���� Ű�� ���������� �ٷ� case �б⹮���� ���� InputActionProc()�� ���ʿ� ȣ���� �ȵǴµ�..?
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
		// �׼� ó��
		
		break;
	}
	*/
	

}

void Player::InputActionProc()
{
	switch (m_dwActionCur) {

		// �ƹ�Ű�� �������� �ʾ��� ��

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
	// �׸��� ���
	pSpriteDib->DrawSprite(eSHADOW, _x, _y, bypDest, iDestWidth, iDestHeight, iDestPitch);

	// �÷��̾� ���
	pSpriteDib->DrawSprite(m_cur_sprite, _x, _y, bypDest, iDestWidth, iDestHeight, iDestPitch);

	// HP ���
	pSpriteDib->DrawSprite(eGUAGE_HP, _x - 35 , _y + 9, bypDest, iDestWidth, iDestHeight, iDestPitch,_HP);
}

void Player::SetActionStand()
{
	// �׼��� �ٲ���� ���� ����.
	if (m_dwActionCur != m_dwActionOld) {
		// ���� �ٶ� ��
		if (m_iDirCur == 0) {
			SetSprite(ePLAYER_STAND_L01, ePLAYER_STAND_L_MAX, dfDELAY_STAND);
		}

		// ������ �ٶ� ��
		else if (m_iDirCur == 1) {
			SetSprite(ePLAYER_STAND_R01, ePLAYER_STAND_R_MAX, dfDELAY_STAND);
		}
	}
}

void Player::SetActionMove()
{
	// �׼��� �ٲ���� ���� ����.
	if (m_dwActionCur != m_dwActionOld) {
		// ���� �ٶ� ��
		if (m_iDirCur == 0) {
			SetSprite(ePLAYER_MOVE_L01, ePLAYER_MOVE_L_MAX, dfDELAY_MOVE);
		}

		// ������ �ٶ� ��
		else if (m_iDirCur == 1) {
			SetSprite(ePLAYER_MOVE_R01, ePLAYER_MOVE_R_MAX, dfDELAY_MOVE);
		}

	}

}

void Player::SetActionAttack1()
{
	_attacking = true;
	// ���� �ٶ� ��
	if (m_iDirCur == 0) {
		SetSprite(ePLAYER_ATTACK1_L01, ePLAYER_ATTACK1_L_MAX, dfDELAY_ATTACK1);
	}

	// ������ �ٶ� ��
	else if (m_iDirCur == 1) {
		SetSprite(ePLAYER_ATTACK1_R01, ePLAYER_ATTACK1_R_MAX, dfDELAY_ATTACK1);
	}

}

void Player::SetActionAttack2()
{
	_attacking = true;

	// ���� �ٶ� ��
	if (m_iDirCur == 0) {
		SetSprite(ePLAYER_ATTACK2_L01, ePLAYER_ATTACK2_L_MAX, dfDELAY_ATTACK2);
	}

	// ������ �ٶ� ��
	else if (m_iDirCur == 1) {
		SetSprite(ePLAYER_ATTACK2_R01, ePLAYER_ATTACK2_R_MAX, dfDELAY_ATTACK2);
	}

}

void Player::SetActionAttack3()
{
	_attacking = true;

	// ���� �ٶ� ��
	if (m_iDirCur == 0) {
		SetSprite(ePLAYER_ATTACK3_L01, ePLAYER_ATTACK3_L_MAX, dfDELAY_ATTACK3);
	}

	// ������ �ٶ� ��
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