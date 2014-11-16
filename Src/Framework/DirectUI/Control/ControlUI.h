#ifndef ControlUI_h__
#define ControlUI_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ControlUI.h
// ������	: 	daviyang35@gmail.com
// ����ʱ��	:	2014-11-08 15:36:37
// ˵��		:	
/////////////////////////////////////////////////////////////*/
#pragma once

typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);

class DIRECTUI_API CControlUI
	: public CObjectUI
{
	friend class CWindowUI;
public:
	CControlUI(void);
	virtual ~CControlUI(void);
	UI_DECLARE_DYNCREATE();

	virtual UINT GetControlFlags() const;
	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface(LPCTSTR lpszClass);

	// һЩ��Ҫ������
	virtual bool IsVisible() const;
	virtual void SetVisible(bool bVisible = true);
	virtual void SetInternVisible(bool bVisible = true); // �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
	virtual bool IsEnabled() const;
	virtual void SetEnabled(bool bEnable = true);
	virtual bool IsMouseEnabled() const;
	virtual void SetMouseEnabled(bool bEnable = true);
	virtual bool IsKeyboardEnabled() const;
	virtual void SetKeyboardEnabled(bool bEnable = true);
	virtual bool IsFocused() const;
	virtual void SetFocus();
	virtual bool IsFloat() const;
	virtual void SetFloat(bool bFloat = true);

protected:
	bool m_bIsVisible;
	bool m_bIsInternVisible;
	bool m_bIsEnabled;
	bool m_bIsMouseEnabled;
	bool m_bIsKeyboardEnabled ;
	bool m_bIsFocused;
	bool m_bIsFloat;
	bool m_bIsSetPos; // ��ֹSetPosѭ������
	bool m_bIsUpdateNeeded;
	bool m_bIsMenuUsed;

public:
	// Tooltip
	virtual LPCTSTR GetToolTip() const;
	virtual void SetToolTip(LPCTSTR lpszText);
	virtual void SetToolTipWidth(int nWidth);
	virtual int GetToolTipWidth( void ) const;		// ����ToolTip��������
private:
	CDuiString m_sText;
	CDuiString m_strToolTip;
	int m_nTooltipWidth;

public:
	// �ؼ��������
	virtual RECT GetRect();						// GetPos
	virtual void SetRect(LPCRECT rc);		// SetPos
	virtual RECT GetInterRect();					// ����HostWindow
	void SetInset(LPRECT rc);
	RECT GetInset();

	// �ı����
	virtual LPCTSTR GetText() const;
	virtual void SetText(LPCTSTR pstrText);

	// λ�����
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual int GetX() const;
	virtual int GetY() const;
	virtual RECT GetPadding() const;
	virtual void SetPadding(RECT rcPadding); // ������߾࣬���ϲ㴰�ڻ���
	virtual SIZE GetFixedXY() const;         // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
	virtual void SetFixedXY(SIZE szXY);      // ��floatΪtrueʱ��Ч
	virtual int GetFixedWidth() const;       // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
	virtual void SetFixedWidth(int cx);      // Ԥ��Ĳο�ֵ
	virtual int GetFixedHeight() const;      // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
	virtual void SetFixedHeight(int cy);     // Ԥ��Ĳο�ֵ
	virtual int GetMinWidth() const;
	virtual void SetMinWidth(int cx);
	virtual int GetMaxWidth() const;
	virtual void SetMaxWidth(int cx);
	virtual int GetMinHeight() const;
	virtual void SetMinHeight(int cy);
	virtual int GetMaxHeight() const;
	virtual void SetMaxHeight(int cy);
	//virtual void SetRelativePos(SIZE szMove,SIZE szZoom);
	//virtual void SetRelativeParentSize(SIZE sz);
	//virtual TRelativePosUI GetRelativePos() const;
	//virtual bool IsRelativePos() const;

	// �˵�
	virtual bool IsContextMenuUsed() const;
	virtual void SetContextMenuUsed(bool bMenuUsed);

	// �ؼ�״̬
	virtual void SetState(UISTATE nState);
	virtual UISTATE GetState(void);

	virtual bool Activate();

	virtual void SetTextForState(LPCTSTR lpszText,UISTATE nState);
	virtual LPCTSTR GetTextForState(UISTATE nState);

	virtual void SetImageForState(LPCTSTR lpszImage,UISTATE nState);
	virtual LPCTSTR GetImageForState(UISTATE nState);

	// 
	DWORD GetBkColor() const;
	void SetBkColor(DWORD dwBackColor);
	LPCTSTR GetBkImage();
	virtual void SetBkImage(LPCTSTR pStrImage);
protected:
	CDuiRect m_rcItem;			// �ؼ���������
	CDuiRect m_rcInset;		// �ڲ�������
	CDuiRect m_rcPadding;	// �߾�
	CDuiSize m_cXY;
	CDuiSize m_cxyFixed;
	CDuiSize m_cxyMin;
	CDuiSize m_cxyMax;
	UISTATE m_uState;
	DWORD m_dwBackColor;
	CDuiString m_sBkImage;
public:
	// Manager
	virtual void SetManager(CWindowUI* pManager, CControlUI* pParent);
	CWindowUI* GetManager();
	CControlUI* GetParent();

protected:
	CControlUI* m_pParent;              //������
	CWindowUI* m_pManager;              //��������

public:
	// Control
	virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);
	virtual bool EventHandler(TEventUI& event);		// ����CWindowUIת������Ϣ�¼�
	//virtual void Invoke(TEventUI& event);						// �ؼ�����ҵ���߼�����
	virtual void Render(IUIRender* pRender,LPCRECT pRcPaint);		// �ؼ������ڲ�״̬��ͼ
	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);

	void Invalidate();
	bool IsUpdateNeeded() const;
	void NeedUpdate();
	void NeedParentUpdate();
	void SetTimer(UINT nTimerID,UINT uElapse);
	void KillTimer(UINT nTimer);

public:
	void	SendNotify(DWORD dwType, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false);


private:
	CEventSource m_OnEvent;
	CEventSource OnNotify;
};

#endif // ControlUI_h__
