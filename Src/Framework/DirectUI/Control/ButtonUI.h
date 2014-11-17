#ifndef ButtonUI_h__
#define ButtonUI_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ButtonUI.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2014-11-16 23:46:28
// ˵��			:	Button
/////////////////////////////////////////////////////////////*/
#pragma once

class CButtonUI
	: public CControlUI
{
public:
	CButtonUI(void);
	virtual ~CButtonUI(void);
	UI_DECLARE_DYNCREATE();

	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface(LPCTSTR lpszClass);
};

#endif // ButtonUI_h__
