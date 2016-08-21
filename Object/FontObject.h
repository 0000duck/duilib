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

namespace DuiLib
{

class UILIB_API FontObject
{
public:
	FontObject(void);
	~FontObject();
	
	CDuiString strFontID;	
	CDuiString strFaceName;

	int nSize;	
	bool bBold;	
	bool bItalic;	
	bool bUnderline;	
	bool bStrikeout;

	HFONT GetFont();
	TEXTMETRIC& GetTextMetric();

private:
	HFONT m_hFont;
	TEXTMETRIC m_TextMetric;
};
}
#endif // FontObject_h__
