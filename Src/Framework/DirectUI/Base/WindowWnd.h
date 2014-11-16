#ifndef WindowWnd_h__
#define WindowWnd_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	WindowWnd.h
// ������	: 	daviyang35@gmail.com
// ����ʱ��	:	2014-11-07 22:23:50
// ˵��		:	Windows���ڰ�װ��
/////////////////////////////////////////////////////////////*/
#pragma once

class DIRECTUI_API CWindowWnd
{
public:
	CWindowWnd(void);
	virtual ~CWindowWnd(void);

public:
	HWND Create(HWND hwndParent, LPCTSTR lpszWindowName, DWORD dwStyle, DWORD dwExStyle,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT);

	void SetAutoDelete(bool bAutoDelete = true);

	void SetWindowStyle(DWORD dwStyle);
	void SetWindowExStyle(DWORD dwExStyle);

	HWND Subclass(HWND hWnd);
	void Unsubclass();

	HWND GetHWND() const;
	operator HWND() const;

	void ShowWindow(bool bShow = true, bool bTakeFocus = true);
	void CenterWindow();	// ���У�֧����չ��Ļ
	void SetIcon(UINT nRes);

	UINT ShowModal();
	void Close(UINT nRet = IDOK);

	LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	void ResizeClient(int cx = -1, int cy = -1);

protected:
	bool RegisterWindowClass();

	virtual LPCTSTR GetWindowClassName() const;
	virtual UINT GetClassStyle() const;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnFinalMessage(HWND hWnd);

	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hWnd;
	WNDPROC m_OldWndProc;
	bool m_bSubclassed;
	bool m_bIsAutoDelete;
};

#endif // WindowWnd_h__
