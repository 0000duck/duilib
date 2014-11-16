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

class DIRECTUI_API ImageObject
{
public:
	ImageObject(void);
	~ImageObject(void);

	void SetImagePath(LPCTSTR lpszImagePath);
	LPCTSTR GetImagePath(void);

	int GetWidth();
	int GetHeight();

public:
	ImageObject* Get();
	void Release();

private:
	int m_nWidth;
	int m_nHeight;
	int m_nAlpha;
	int m_nFrame;
	CDuiRect m_rc9Grid;	// �Ź���
	CDuiString m_strFilePath;
	CDuiString m_strKey;
};

#endif // ImageObject_h__
