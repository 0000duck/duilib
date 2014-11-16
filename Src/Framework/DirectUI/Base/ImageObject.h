#ifndef ImageObject_h__
#define ImageObject_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ImageObject.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2014-11-09 15:30:54
// ˵��			:	��ͼ��Դ��װ����	
/////////////////////////////////////////////////////////////*/
#pragma once

class DIRECTUI_API CImageObject
{
public:
	CImageObject(void);
	~CImageObject(void);

	void SetImagePath(LPCTSTR lpszImagePath);
	LPCTSTR GetImagePath(void);

	int GetWidth();
	int GetHeight();

public:
	CImageObject* Get();
	void Release();

private:
	int m_nWidth;
	int m_nHeight;
	int m_nAlpha;
	int m_nFrame;
	int m_arrayState[5];
	CDuiRect m_rc9Grid;	// �Ź���
	CDuiString m_strFilePath;
	CDuiString m_strKey;
};

#endif // ImageObject_h__
