// Player.cpp

#include "stdafx.h"
#include "Player.h"


Player::Player(int x, int y)
{
	m_dwActionInput = 0;
	_x = x;
	_y = y;
}


Player::~Player()
{
}


void Player::ActionInput(DWORD dwAction)
{
	m_dwActionInput = dwAction;
}