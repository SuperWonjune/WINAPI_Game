//FrameCheck.h

#pragma once

/*
�⺻ ���� ����

�ʴ� 50fps�� �����̶� ����.
while���� ȣ��Ǵ� ������ 20ms���� �Ѵ�.

1. ���� �Ҵ�� �ð����� ���� �ð����� ������ ������.
�׷� ��쿣 �ּ� ȣ�� ���� �ð� ��ŭ ��ٷ��ش�.
���� ��� 5ms�� �ɷȴٰ� �Ѵٸ� Sleep(15)�� ���ش�.

2. �Ҵ�� �ð����� �� ū �ð��� �ɷȴٸ�? ���ϰ� �Ͼ�ٴ� �ǹ�.
surplusTime �� ���� �Ҵ�� �ð����� �� ���ϵ� �ð��� ���� ���ذ���.
�̷��� ��� ���ذ��ٰ� �ð��� ���� ���� ȣ��Ǵ� ������ �ð����� �� �������� 
�ð� ���� ��ŭ�� ���� ���ְ� �������� ������ �κ��� �ѹ� ��ŵ�Ѵ�.

����)
ù��° �������� 25ms�� �ɷȴٰ� �Ѵٸ� surplusTime�� 5�� ���Ѵ�.
�ι�° �����ӿ� 34ms�� �ɷȴٸ� 14�� ���Ѵ�
����° �����ӿ� 26ms�� �ɷȴٰ� �ϸ� 6�� ���Ѵ�.
surplusTime�� �� 25�� �Ǿ����Ƿ� 20�� ���ְ�, �������� �ϳ� �����Ѵ�.

*/

class FrameCheck
{
public:
	FrameCheck(size_t iFps);
	virtual ~FrameCheck();

	bool checkFrame();



	// �ѹ� ������ üũ�� �ϰ� �� ���� ������üũ�� �� �� ���� �ɸ� �ð�.
	size_t elapsedTime;

	// �����Ӱ� ������ ������ ms�� �Ѿ �� �� ���̸� �����س��� ����
	// ����ؼ� ���ذ���.
	size_t surplusTime;	

private:
	// ���� ���� ������ fps
	size_t _fps;
	size_t _timePerFunction;
	
	
};
