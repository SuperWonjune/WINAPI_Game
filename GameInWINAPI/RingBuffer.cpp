#include "RingBuffer.h"
#include "stdafx.h"


CRingBuffer::CRingBuffer(int iBufferSize)
{
	Init(iBufferSize);
}


CRingBuffer::~CRingBuffer()
{
	if (buffer != NULL) {
		delete buffer;
	}
}


void CRingBuffer::Init(int iBufferSize)
{
	front = 0;
	rear = 0;

	// ���� ������ ����
	bufferSize = iBufferSize;

	// ���� �Ҵ�
	buffer = new char[bufferSize];

	
}

int	CRingBuffer::GetBufferSize(void)
{
	return bufferSize;
}

int	CRingBuffer::GetUseSize(void)
{
	// rear >= front �� ���
	if (rear >= front) {
		return rear - front;
	}

	// rear < front �� ���
	else {
		return bufferSize + (rear - front);
	}
}

int	CRingBuffer::GetFreeSize(void)
{
	// ť�� ����á�� ����� ����
	// front - 1 = rear

	if (front > rear) {
		return front - rear - 1;
	}
	else {
		return bufferSize + (front - rear - 1);
	}
}

int	CRingBuffer::GetNotBrokenGetSize(void)
{
	return bufferSize - rear;
}

int	CRingBuffer::GetNotBrokenPutSize(void)
{
	return bufferSize - front;
}

int	CRingBuffer::Enqueue(char *chpData, int iSize)
{
	// ũ�� ����ó��
	// �����Ϸ��� ũ�Ⱑ freeSize���� �� ũ�� freeSize��ŭ�� ����
	if (iSize > GetFreeSize()) {
		iSize = GetFreeSize();
	}

	if (GetFreeSize() == 0) {
		//QUEUE FULL;
		return 0;
	}


	// front > rear�� ���
	if (front > rear) {
		// iSize��ŭ buffer�� �޸� ����
		memcpy(GetWriteBufferPtr(), chpData, iSize);

		// rear index ����
		rear += iSize;
		rear = GetIndex(rear);

	}

	// rear >= front�� ���
	else {
		// �����Ϸ��� ũ�Ⱑ 0�� �������� �Ѿ������ ���
		if (iSize > GetNotBrokenGetSize()) {
			// ���� rear���� 0������ ������ ����
			memcpy(GetWriteBufferPtr(), chpData, GetNotBrokenGetSize());

			// 0���� �ʰ��� ���������� ����
			memcpy(buffer, chpData + GetNotBrokenGetSize(), iSize - GetNotBrokenGetSize());

			// rear index ����
			rear = rear + iSize;
			rear = GetIndex(rear);
		}

		// �����Ϸ��� ũ�Ⱑ 0 �������� ������ ���� ���
		else {
			// iSize��ŭ �޸� ����
			memcpy(GetWriteBufferPtr(), chpData, iSize);

			// rear index ����
			rear = rear + iSize;
			rear = GetIndex(rear);
		}

	}
	return iSize;
}

int	CRingBuffer::Dequeue(char *chpDest, int iSize)
{
	// ��� ���� �뷮���� �� ū�� ���������ϸ� ������� �뷮���� ����
	if (iSize > GetUseSize()) {
		iSize = GetUseSize();
	}


	// rear >= front �� ���
	if (rear >= front) {

		// chpDest�� buffer�� front���� iSize��ŭ�� �����͸� ���� 
		memcpy(chpDest, GetReadBufferPtr(), iSize);

		// front index ����
		front += iSize;
		front = GetIndex(front);
	}

	// rear < front �� ���
	else {
		// �о���̷��� ũ�Ⱑ 0�� �������� �Ѿ���������
		if (iSize > GetNotBrokenPutSize()) {
			// ���� front���� 0������ ������ chpDest�� ����
			memcpy(chpDest, GetReadBufferPtr(), GetNotBrokenPutSize());

			// 0���� �ʰ��� ���������� chpDest�� ����
			memcpy(chpDest + GetNotBrokenPutSize(), buffer, iSize - GetNotBrokenPutSize());

			// front index ����
			front = front + iSize;
			front = GetIndex(front);
		}

		// 0�������� �� �Ѿ��� ���
		else {
			// iSize��ŭ chpDest�� �޸� ����
			memcpy(chpDest, GetReadBufferPtr(), iSize);

			// front index ����
			front = front + iSize;
			front = GetIndex(front);
		}

	}

	return iSize;
}


int	CRingBuffer::Peek(char *chpDest, int iSize)
{
	// ��� ���� �뷮���� �� ū�� �������� �ϸ� ������� �뷮���� ����
	if (iSize > GetUseSize()) {
		iSize = GetUseSize();
	}


	// rear >= front �� ���
	if (rear >= front) {

		// chpDest�� buffer�� front���� iSize��ŭ�� �����͸� ���� 
		memcpy(chpDest, GetReadBufferPtr(), iSize);

	}

	// rear < front �� ���
	else {
		// �о���̷��� ũ�Ⱑ 0�� �������� �Ѿ���������
		if (iSize > GetNotBrokenPutSize()) {
			// ���� front���� 0������ ������ chpDest�� ����
			memcpy(chpDest, GetReadBufferPtr(), GetNotBrokenPutSize());

			// 0���� �ʰ��� ���������� chpDest�� ����
			memcpy(chpDest + GetNotBrokenPutSize(), buffer, iSize - GetNotBrokenPutSize());
		}

		// 0�������� �� �Ѿ��� ���
		else {
			// iSize��ŭ chpDest�� �޸� ����
			memcpy(chpDest, GetReadBufferPtr(), iSize);
		}

	}
	return iSize;
}


int CRingBuffer::MoveReadPos(int iSize)
{
	if (iSize > GetUseSize()) {
		iSize = GetUseSize();
	}
	front = front + iSize;
	front = GetIndex(front);

	return iSize;
}

int CRingBuffer::MoveWritePos(int iSize)
{
	if (iSize > GetFreeSize()) {
		iSize = GetFreeSize();
	}

	rear = rear + iSize;
	rear = GetIndex(rear);

	return iSize;
}

void CRingBuffer::ClearBuffer(void)
{
	front = 0;
	rear = 0;
}

char * CRingBuffer::GetBufferPtr(void)
{
	return buffer;
}


char * CRingBuffer::GetReadBufferPtr(void)
{
	return buffer + front;
}


char * CRingBuffer::GetWriteBufferPtr(void)
{
	return buffer + rear;
}