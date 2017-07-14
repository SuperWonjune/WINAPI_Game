//FrameCheck.h

#pragma once

/*
기본 동작 원리

초당 50fps의 게임이라 가정.
while문이 호출되는 간격은 20ms여야 한다.

1. 만약 할당된 시간보다 적은 시간으로 수행이 끝났다.
그럴 경우엔 최소 호출 간격 시간 만큼 기다려준다.
예를 들어 5ms가 걸렸다고 한다면 Sleep(15)를 해준다.

2. 할당된 시간보다 더 큰 시간이 걸렸다면? 부하가 일어났다는 의미.
surplusTime 에 기존 할당된 시간보다 더 부하된 시간의 차를 더해간다.
이렇게 계속 더해가다가 시간의 차의 합이 호출되는 간격의 시간보다 더 많아지면 
시간 간격 만큼의 값을 빼주고 프레임의 렌더링 부분을 한번 스킵한다.

예시)
첫번째 프레임이 25ms가 걸렸다고 한다면 surplusTime에 5를 더한다.
두번째 프레임에 34ms가 걸렸다면 14를 더한다
세번째 프레임에 26ms가 걸렸다고 하면 6을 더한다.
surplusTime이 총 25가 되었으므로 20을 빼주고, 렌더링을 하나 생략한다.

*/

class FrameCheck
{
public:
	FrameCheck(size_t iFps, HWND * ipHWnd);
	virtual ~FrameCheck();

	// 게임 내에서 매 프레임마다 호출되는 함수.
	// 프레임을 생략할 상황이 아닌경우 true를 리턴, 생략해야 할 경우 false를 리턴
	bool checkFrame();

	

private:
	HWND * pHWnd;
	// 이전 측정 시간
	size_t _prevTime;
	// 현재 측정된 시간
	size_t _curTime;

	// 한번 프레임 체크를 하고 그 다음 프레임체크를 할 때 까지 걸린 시간.
	size_t _elapsedTime;

	// 프레임간 간격이 설정된 ms를 넘어갈 때 그 차이를 저장해놓는 변수
	// 계속해서 더해간다.
	size_t _surplusTime;

	// 게임 내에 설정된 fps
	size_t _fps;
	size_t _timePerFunction;
	
	
};

