#ifndef FontObject_h__
#define FontObject_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	FontObject.h
// ������		: 	daviyang35@gmail.com
// ����ʱ��	:	2014-11-09 16:55:32
// ˵��			:	Font Object
/////////////////////////////////////////////////////////////*/
#pragma once

class DIRECTUI_API CFontObject
{
public:
	CFontObject(void);
	~CFontObject(void);

private:
	HFONT m_hFont;
	CDuiString sFontName;
	int iSize;
	bool bBold;
	bool bUnderline;
	bool bItalic;
	TEXTMETRIC tm;
};

#endif // FontObject_h__
