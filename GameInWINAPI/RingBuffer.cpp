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

	// 버퍼 사이즈 설정
	bufferSize = iBufferSize;

	// 버퍼 할당
	buffer = new char[bufferSize];

	
}

int	CRingBuffer::GetBufferSize(void)
{
	return bufferSize;
}

int	CRingBuffer::GetUseSize(void)
{
	// rear >= front 일 경우
	if (rear >= front) {
		return rear - front;
	}

	// rear < front 일 경우
	else {
		return bufferSize + (rear - front);
	}
}

int	CRingBuffer::GetFreeSize(void)
{
	// 큐가 가득찼을 경우의 조건
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
	// 크기 예외처리
	// 복사하려는 크기가 freeSize보다 더 크면 freeSize만큼만 복사
	if (iSize > GetFreeSize()) {
		iSize = GetFreeSize();
	}

	if (GetFreeSize() == 0) {
		//QUEUE FULL;
		return 0;
	}


	// front > rear인 경우
	if (front > rear) {
		// iSize만큼 buffer로 메모리 복사
		memcpy(GetWriteBufferPtr(), chpData, iSize);

		// rear index 조정
		rear += iSize;
		rear = GetIndex(rear);

	}

	// rear >= front인 경우
	else {
		// 복사하려는 크기가 0을 기점으로 넘어가버렸을 경우
		if (iSize > GetNotBrokenGetSize()) {
			// 기존 rear에서 0까지의 범위를 복사
			memcpy(GetWriteBufferPtr(), chpData, GetNotBrokenGetSize());

			// 0에서 초과된 범위까지를 복사
			memcpy(buffer, chpData + GetNotBrokenGetSize(), iSize - GetNotBrokenGetSize());

			// rear index 조정
			rear = rear + iSize;
			rear = GetIndex(rear);
		}

		// 복사하려는 크기가 0 기점으로 넘지는 않을 경우
		else {
			// iSize만큼 메모리 복사
			memcpy(GetWriteBufferPtr(), chpData, iSize);

			// rear index 조정
			rear = rear + iSize;
			rear = GetIndex(rear);
		}

	}
	return iSize;
}

int	CRingBuffer::Dequeue(char *chpDest, int iSize)
{
	// 사용 중인 용량보다 더 큰걸 빼내려고하면 사용중인 용량으로 설정
	if (iSize > GetUseSize()) {
		iSize = GetUseSize();
	}


	// rear >= front 인 경우
	if (rear >= front) {

		// chpDest로 buffer의 front에서 iSize만큼의 데이터를 복사 
		memcpy(chpDest, GetReadBufferPtr(), iSize);

		// front index 설정
		front += iSize;
		front = GetIndex(front);
	}

	// rear < front 인 경우
	else {
		// 읽어들이려는 크기가 0을 기점으로 넘어버렸을경우
		if (iSize > GetNotBrokenPutSize()) {
			// 기존 front에서 0까지의 범위를 chpDest로 복사
			memcpy(chpDest, GetReadBufferPtr(), GetNotBrokenPutSize());

			// 0에서 초과된 범위까지를 chpDest로 복사
			memcpy(chpDest + GetNotBrokenPutSize(), buffer, iSize - GetNotBrokenPutSize());

			// front index 조정
			front = front + iSize;
			front = GetIndex(front);
		}

		// 0기점으로 안 넘었을 경우
		else {
			// iSize만큼 chpDest로 메모리 복사
			memcpy(chpDest, GetReadBufferPtr(), iSize);

			// front index 조정
			front = front + iSize;
			front = GetIndex(front);
		}

	}

	return iSize;
}


int	CRingBuffer::Peek(char *chpDest, int iSize)
{
	// 사용 중인 용량보다 더 큰걸 읽으려고 하면 사용중인 용량으로 설정
	if (iSize > GetUseSize()) {
		iSize = GetUseSize();
	}


	// rear >= front 인 경우
	if (rear >= front) {

		// chpDest로 buffer의 front에서 iSize만큼의 데이터를 복사 
		memcpy(chpDest, GetReadBufferPtr(), iSize);

	}

	// rear < front 인 경우
	else {
		// 읽어들이려는 크기가 0을 기점으로 넘어버렸을경우
		if (iSize > GetNotBrokenPutSize()) {
			// 기존 front에서 0까지의 범위를 chpDest로 복사
			memcpy(chpDest, GetReadBufferPtr(), GetNotBrokenPutSize());

			// 0에서 초과된 범위까지를 chpDest로 복사
			memcpy(chpDest + GetNotBrokenPutSize(), buffer, iSize - GetNotBrokenPutSize());
		}

		// 0기점으로 안 넘었을 경우
		else {
			// iSize만큼 chpDest로 메모리 복사
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