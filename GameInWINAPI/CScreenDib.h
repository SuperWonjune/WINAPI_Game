// CScreenDib.h

#pragma once

class CScreenDib
{
public:

	CScreenDib(int iWidth, int iHeight, int iColorBit);
	virtual ~CScreenDib();

protected:

	void CreateDibBuffer(int iWidth, int iHeight, int iColorBit);
	void ReleaseDibBuffer(void);

public:

	void DrawBuffer(HWND hWnd, int iX = 0 , int iY = 0);

	BYTE *GetDibBuffer(void) { return m_bypBuffer; }
	int GetWidth(void) { return m_iWidth; }
	int GetHeight(void) { return m_iHeight; }
	int GetPitch(void) { return m_iPitch; }

protected:

	BITMAPINFO m_stDibInfo;
	BYTE *m_bypBuffer;

	int m_iWidth;
	int m_iHeight;
	int m_iPitch;
	int m_iColorBit;
	int m_iBufferSize;
};

