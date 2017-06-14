// Player.h

#include "BaseObject.h"
#include "DefineEnum.h"

#pragma once
class Player : public BaseObject
{
public:
	Player(int x, int y);
	virtual ~Player();

	void ActionInput(DWORD dwAction);

protected:
	DWORD m_dwActionInput;
};

