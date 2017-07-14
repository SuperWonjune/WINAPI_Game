// Player.h

#include "BaseObject.h"
#include "DefineEnum.h"


#pragma once
class Player : public BaseObject
{
public:
	Player(int x, int y);
	virtual ~Player();


	virtual void Action();
	void ActionInput(DWORD dwAction);
	void ActionProc();
	void InputActionProc();
	
	virtual void draw(CSpriteDib * pSpriteDib, BYTE * bypDest, int iDestWidth, int iDestHeight, int iDestPitch);

	void SetActionStand();
	void SetActionMove();
	void SetActionAttack1();
	void SetActionAttack2();
	void SetActionAttack3();

	void CheckBoundary();

protected:
	DWORD m_dwActionCur;
	DWORD m_dwActionOld;
	int _HP;
	int _player_X_Speed;
	int _player_Y_Speed;

	// ���� 0�̸� ����, 1�̸� ������
	int m_iDirCur;
	int m_iDirOld;

	bool _attacking;
};

