//FrameCheck.cpp

#include "stdafx.h"
#include "FrameCheck.h"


FrameCheck::FrameCheck(size_t iFps, HWND * ipHWnd)
{
	_fps = iFps;
	_timePerFunction = 1000 / _fps;

	_curTime = 0;
	_prevTime = 0;
	_elapsedTime = 0;
	_surplusTime = 0;
	pHWnd = ipHWnd;
}


FrameCheck::~FrameCheck()
{

}


bool FrameCheck::checkFrame()
{
	// ���� ������ �� �����Ӹ��� ȣ���.
	// ���� ������ �����ϰ�
	// ��ŵ�� ��Ȳ�̶�� false�� ����, �ƴϸ� true�� ����


	// ��ó�� ����ɶ�. ���� ȣ���� ���� �ð� �����ϰ� �ٷ� ��������
	if (_prevTime == 0) {
		_prevTime = timeGetTime();
		return true;
	}

	// ���� �Լ��� ����� �ð� ����
	_curTime = timeGetTime();

	// �� �����Ӱ��� ���� �ð� ���� ���
	_elapsedTime = _curTime - _prevTime;

	_prevTime = _curTime;
	

	// 1. �Ҵ�� �� ������ �ð����� �� ���� ������ ������ ���
	if (_elapsedTime < _timePerFunction) {
		// �� ���̸�ŭ ������
		Sleep(_timePerFunction - _elapsedTime);
		HDC hdc = GetDC(*pHWnd);
		TCHAR str1[128];
		wsprintf(str1, L"%d", _timePerFunction - _elapsedTime);
		TextOut(hdc, 0, 20, str1, wcslen(str1));
		ReleaseDC(*pHWnd, hdc);
		return true;
	}

	// 2. �Ҵ�� �ð����� �� ū �ð��� �ɷ��� ��. �� ���ϰ� �Ͼ�� ��
	else {

		// �� ���̸�ŭ surplusTime ������ ������
		_surplusTime += _elapsedTime - _timePerFunction;

		if (_surplusTime > _timePerFunction) {
			_surplusTime -= _timePerFunction;

			return false;
		}

		return true;
	}
}