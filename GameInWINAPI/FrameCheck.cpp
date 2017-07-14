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
	// 게임 내에서 매 프레임마다 호출됨.
	// 각종 연산을 수행하고
	// 스킵할 상황이라면 false를 리턴, 아니면 true를 리턴


	// 맨처음 실행될때. 다음 호출을 위한 시간 설정하고 바로 빠져나감
	if (_prevTime == 0) {
		_prevTime = timeGetTime();
		return true;
	}

	// 현재 함수가 실행된 시간 측정
	_curTime = timeGetTime();

	// 전 프레임과의 실행 시간 차이 계산
	_elapsedTime = _curTime - _prevTime;

	_prevTime = _curTime;
	

	// 1. 할당된 매 프레임 시간보다 더 빨리 연산이 끝났을 경우
	if (_elapsedTime < _timePerFunction) {
		// 그 차이만큼 쉬어줌
		Sleep(_timePerFunction - _elapsedTime);
		HDC hdc = GetDC(*pHWnd);
		TCHAR str1[128];
		wsprintf(str1, L"%d", _timePerFunction - _elapsedTime);
		TextOut(hdc, 0, 20, str1, wcslen(str1));
		ReleaseDC(*pHWnd, hdc);
		return true;
	}

	// 2. 할당된 시간보다 더 큰 시간이 걸렸을 때. 즉 부하가 일어났을 때
	else {

		// 그 차이만큼 surplusTime 변수에 더해줌
		_surplusTime += _elapsedTime - _timePerFunction;

		if (_surplusTime > _timePerFunction) {
			_surplusTime -= _timePerFunction;

			return false;
		}

		return true;
	}
}