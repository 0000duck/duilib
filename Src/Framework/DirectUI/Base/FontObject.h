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

class DIRECTUI_API FontObject
{
public:
	FontObject(void);
	~FontObject(void);

	HFONT GetFont();
	LOGFONT& GetLogFont();
	int GetHeight();
	void SetFaceName(LPCTSTR lpszFace);
	void SetFontSize(int nSize);
	void SetBold(bool bBold);
	void SetUnderline(bool bUnderline);
	void SetItalic(bool bItalic);
	void SetStrikeout(bool bStrikeout);

protected:
	LOGFONT m_lfFont;
	HFONT m_hFont;
};

#endif // FontObject_h__
