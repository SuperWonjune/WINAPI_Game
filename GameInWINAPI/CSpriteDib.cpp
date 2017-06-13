// CSpriteDib.cpp

#include "stdafx.h"
#include "CSpriteDib.h"


CSpriteDib::CSpriteDib(int iMaxSprite, DWORD dwColorKey)
{
	m_iMaxSprite = iMaxSprite;
	m_dwColorKey = dwColorKey;

	m_stpSprite = NULL;

	// 스프라이트 최대 갯수만큼 할당
	m_stpSprite = new st_SPRITE[m_iMaxSprite];
	memset(m_stpSprite, 0, sizeof(st_SPRITE) * m_iMaxSprite);
}


CSpriteDib::~CSpriteDib()
{
	int iCount;

	for (iCount = 0; iCount < m_iMaxSprite; iCount++) {
		ReleaseSprite(iCount);
	}
}

BOOL CSpriteDib::LoadDibSprite(int iSpriteIndex, WCHAR *szFileName, int iCenterPointX, int iCenterPointY)
{
	HANDLE hFile;
	DWORD dwRead;
	int iPitch;
	int iImageSize;
	int iCount;

	BITMAPFILEHEADER stFileHeader;
	BITMAPINFOHEADER stInfoHeader;

	hFile = CreateFile(szFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile) {
		return false;
	}

	ReleaseSprite(iSpriteIndex);
	ReadFile(hFile, &stFileHeader, sizeof(BITMAPFILEHEADER), &dwRead, NULL);

	if (0x4d42 == stFileHeader.bfType) {

		ReadFile(hFile, &stInfoHeader, sizeof(BITMAPINFOHEADER), &dwRead, NULL);
		if (32 == stInfoHeader.biBitCount) {
			// 피치 값 계산
			iPitch = (stInfoHeader.biWidth * 4) + 3 & ~3;

			// 스프라이트 구조체에 크기 저장
			m_stpSprite[iSpriteIndex].iWidth = stInfoHeader.biWidth;
			m_stpSprite[iSpriteIndex].iHeight = stInfoHeader.biHeight;
			m_stpSprite[iSpriteIndex].iPitch = iPitch;

			// 이미지의 전체 크기 계산, 메모리 할당.
			iImageSize = iPitch * stInfoHeader.biHeight;
			m_stpSprite[iSpriteIndex].bypImage = new BYTE[iImageSize];


			// 버퍼로 읽음

			BYTE *bypTempBuffer = new BYTE[iImageSize];
			BYTE *bypSpriteTemp = m_stpSprite[iSpriteIndex].bypImage;
			BYTE *bypTurnTemp;

			ReadFile(hFile, bypTempBuffer, iImageSize, &dwRead, NULL);

			// 뒤집기
			bypTurnTemp = bypTempBuffer + iPitch * (stInfoHeader.biHeight - 1);

			for (iCount = 0; iCount < stInfoHeader.biHeight; iCount++) {
				memcpy(bypSpriteTemp, bypTurnTemp, iPitch);
				bypSpriteTemp += iPitch;
				bypTurnTemp -= iPitch;
			}
			delete[] bypTempBuffer;

			m_stpSprite[iSpriteIndex].iCenterPointX - iCenterPointX;
			m_stpSprite[iSpriteIndex].iCenterPointY - iCenterPointY;
			CloseHandle(hFile);
			return TRUE;
		}
	}

	CloseHandle(hFile);
	return FALSE;
}

void CSpriteDib::ReleaseSprite(int iSpriteIndex)
{
	if (m_iMaxSprite <= iSpriteIndex) {
		// 최대갯수 초과
		return;
	}

	if (NULL != m_stpSprite[iSpriteIndex].bypImage) {
		delete[] m_stpSprite[iSpriteIndex].bypImage;
		memset(&m_stpSprite[iSpriteIndex], 0, sizeof(st_SPRITE));
	}

}

void CSpriteDib::DrawSprite(int iSpriteIndex, int iDrawX, int iDrawY,
	BYTE *bypDest, int iDestWidth, int iDestHeight, int iDestPitch, int iDrawLen)

{
	// 최대치 초과
	if (iSpriteIndex >= m_iMaxSprite) {
		return;
	}

	// 로드 실패
	if (m_stpSprite[iSpriteIndex].bypImage == NULL) {
		return;
	}

	st_SPRITE *stpSprite = &m_stpSprite[iSpriteIndex];

	// 사이즈들 저장
	int iSpriteWidth = stpSprite->iWidth;
	int iSpriteHeight = stpSprite->iHeight;
	int iCountX, iCountY;

	// 스케일 비율 설정
	iSpriteWidth = iSpriteWidth * iDrawLen / 100;

	DWORD *dwpDest = (DWORD *)bypDest;
	DWORD *dwpSprite = (DWORD *)(stpSprite->bypImage);

	// 출력 중점 처리
	iDrawX = iDrawX - stpSprite->iCenterPointX;
	iDrawY = iDrawY - stpSprite->iCenterPointY;

	// 클리핑 적용
	// 상단
	if (0 > iDrawY) {
		iSpriteHeight = iSpriteHeight - (-iDrawY);
		dwpSprite = (DWORD *)(stpSprite->bypImage + stpSprite->iPitch * (iDrawY));

		iDrawY = 0;
	}

	// 하단
	if (iDestHeight <= iDrawY + stpSprite->iHeight) {
		iSpriteHeight -= ((iDrawY + stpSprite->iHeight) - iDestHeight);
	}

	// 좌측
	if (0 > iDrawX) {
		iSpriteWidth = iSpriteWidth - (-iDrawX);
		dwpSprite = dwpSprite + (-iDrawX);

		iDrawX = 0;
	}

	// 우측
	if (iDestWidth <= iDrawX + stpSprite->iWidth) {
		iSpriteWidth -= ((iDrawX + stpSprite->iWidth) - iDestWidth);
	}

	// 찍을 그림 없으면 종료
	if (iSpriteWidth <= 0 || iSpriteHeight <= 0) {
		return;
	}

	// 화면 픽셀 찍을 위치로 이동
	dwpDest = (DWORD *)(((BYTE *)(dwpDest + iDrawX) + (iDrawY * iDestPitch)));

	BYTE *bypDestOrigin = (BYTE *)dwpDest;
	BYTE *bypSpriteOrigin = (BYTE *)dwpSprite;

	for (iCountY = 0; iSpriteHeight > iCountY; iCountY++) {
		for (iCountX = 0; iSpriteWidth > iCountX; iCountX++) {
			// 칼라키 처리
			if (m_dwColorKey != (*dwpSprite & 0x00ffffff)) {
				*dwpDest = *dwpSprite;
			}

			dwpDest++;
			dwpSprite++;
		}
		// 다음줄로 이동
		bypDestOrigin = bypDestOrigin + iDestPitch;
		bypSpriteOrigin = bypSpriteOrigin + stpSprite->iPitch;

		dwpDest = (DWORD *)bypDestOrigin;
		dwpSprite = (DWORD *)bypSpriteOrigin;
	}
		
}

void CSpriteDib::DrawImage(int iSpriteIndex, int iDrawX, int iDrawY,
	BYTE *bypDest, int iDestWidth, int iDestHeight, int iDestPitch, int iDrawLen)
{
	// 최대치 초과
	if (iSpriteIndex >= m_iMaxSprite) {
		return;
	}

	// 로드 실패
	if (m_stpSprite[iSpriteIndex].bypImage == NULL) {
		return;
	}

	st_SPRITE *stpSprite = &m_stpSprite[iSpriteIndex];

	// 사이즈들 저장
	int iSpriteWidth = stpSprite->iWidth;
	int iSpriteHeight = stpSprite->iHeight;
	int iCountY;

	// 스케일 비율 설정
	iSpriteWidth = iSpriteWidth * iDrawLen / 100;

	DWORD *dwpDest = (DWORD *)bypDest;
	DWORD *dwpSprite = (DWORD *)(stpSprite->bypImage);

	// 출력 중점 처리
	iDrawX = iDrawX - stpSprite->iCenterPointX;
	iDrawY = iDrawY - stpSprite->iCenterPointY;

	// 클리핑 적용
	// 상단
	if (0 > iDrawY) {
		iSpriteHeight = iSpriteHeight - (-iDrawY);
		dwpSprite = (DWORD *)(stpSprite->bypImage + stpSprite->iPitch * (iDrawY));

		iDrawY = 0;
	}

	// 하단
	if (iDestHeight <= iDrawY + stpSprite->iHeight) {
		iSpriteHeight -= ((iDrawY + stpSprite->iHeight) - iDestHeight);
	}

	// 좌측
	if (0 > iDrawX) {
		iSpriteWidth = iSpriteWidth - (-iDrawX);
		dwpSprite = dwpSprite + (-iDrawX);

		iDrawX = 0;
	}

	// 우측
	if (iDestWidth <= iDrawX + stpSprite->iWidth) {
		iSpriteWidth -= ((iDrawX + stpSprite->iWidth) - iDestWidth);
	}

	// 찍을 그림 없으면 종료
	if (iSpriteWidth <= 0 || iSpriteHeight <= 0) {
		return;
	}

	// 화면 픽셀 찍을 위치로 이동
	dwpDest = (DWORD *)(((BYTE *)(dwpDest + iDrawX) + (iDrawY * iDestPitch)));

	for (iCountY = 0; iSpriteHeight > iCountY; iCountY++) {
		memcpy(dwpDest, dwpSprite, iSpriteWidth * 4);

		// 다음줄로 이동
		dwpDest = (DWORD *)((BYTE*)dwpDest + iDestPitch);
		dwpSprite = (DWORD *)((BYTE*)dwpSprite + stpSprite->iPitch);
	}
}