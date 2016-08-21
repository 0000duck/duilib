#ifndef ImageObject_h__
#define ImageObject_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ImageObject.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2014-11-09 15:30:54
// ˵��			:	��ͼ��Դ��װ����	
��ͼ��Դ����������������ͬһ��ͼƬ����
/////////////////////////////////////////////////////////////*/
#pragma once


namespace DuiLib
{

class UILIB_API ImageObject
{
public:
	void Release();
	ImageObject* Get();

public:
	ImageObject();
	ImageObject(HBITMAP hBitmap);
	ImageObject(HICON hIcon);
	ImageObject(BYTE* pPixels, int nWidth, int nHeight);
	virtual ~ImageObject(void);

	void SetHBitmap(HBITMAP hBitmap);
	HBITMAP  GetHBitmap();

	void SetHIcon(HICON hIcon);
	HICON  GetHIcon();

	void SetPixels(BYTE* pPixels, int nWidth, int nHeight);
	BYTE*  GetPixels();

public:
	void    Init();
	void    Desotry();

private:
	TImageData* m_pImageData;
	int m_nAlpha;
	DWORD m_dwMask;
	bool m_bHole;
	bool m_bXTiled;
	bool m_bYTiled;
	CDuiRect m_rcDest;
	CDuiRect m_rcSource;
	CDuiRect m_rc9Grid;	// �Ź���
	CDuiString m_strFilePath;
};

}
#endif // ImageObject_h__
