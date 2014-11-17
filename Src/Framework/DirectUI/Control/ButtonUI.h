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
	UINT GetControlFlags() const;

	bool Activate();
	void SetEnabled(bool bEnable = true);

	virtual bool EventHandler(TEventUI& event);
	virtual void Render(IUIRender* pRender,LPCRECT pRcPaint);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);

};

#endif // ButtonUI_h__
