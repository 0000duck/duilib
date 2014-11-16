#ifndef ScrollBarUI_h__
#define ScrollBarUI_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ScrollBarUI.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2014-11-14 9:20:00
// ˵��			:	������
/////////////////////////////////////////////////////////////*/
#pragma once
#include "Control/ControlUI.h"

class DIRECTUI_API CScrollBarUI
	: public CControlUI
{
public:
	CScrollBarUI(void);
	virtual ~CScrollBarUI(void);
	UI_DECLARE_DYNCREATE();

	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface(LPCTSTR lpszClass);

};

#endif // ScrollBarUI_h__
