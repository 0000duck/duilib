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

class DIRECTUI_API CButtonUI
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

public:
	void SetNormalImage(LPCTSTR lpszImageString);

private:
	// �����ַ���
	CDuiString m_strNormalImage;
	CDuiString m_strHoverImage;
	CDuiString m_strPushedImage;
	CDuiString m_strFocusedImage;
	CDuiString m_strDisabledImage;

	CDuiString m_strForeHoverImage;
	CDuiString m_strForePushedImage;

	// �������ͼƬ����
	ImageObject *m_pNormalImage;
	ImageObject *m_pHoverImage;
	ImageObject *m_pPushedImage;
	ImageObject *m_pFocusedImage;
	ImageObject *m_pDisabledImage;

	ImageObject *m_pForeHoverImage;
	ImageObject *m_pForePushedImage;
};

#endif // ButtonUI_h__
