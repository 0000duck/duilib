#ifndef WindowAnimation_h__
#define WindowAnimation_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	WindowAnimation.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2015-05-23 22:14:17
// ˵��			:	���ڶ�������
/////////////////////////////////////////////////////////////*/
#pragma once

namespace DuiLib
{

class CWindowAnimation
	: public CAction
{
	typedef enum _enWindowAnimationState
	{
		WindowAnimationState_Show = 0,
		WindowAnimationState_Hide,
		WindowAnimationState_Close,
		WindowAnimationState_None,
	}WindowAnimationState;
public:
	CWindowAnimation(void);
	virtual ~CWindowAnimation(void);

	virtual void Start( CWindowUI *pWindow );

	void SetAnimationState(WindowAnimationState state);

	virtual LPCTSTR GetClass();

protected:
	virtual void startWithTarget(CObjectUI* pActionTarget);

	virtual void onFinished();

	WindowAnimationState m_AnimationState;


	HWND m_hWnd;
	RECT m_rcWindow;
	SIZE m_szWindow;
	RECT m_rcAnimationDC;
	SIZE m_szAnimationDC;
	bool m_bLayerWindow;
	CWindowUI *m_pWindow;

	BLENDFUNCTION m_BlendFun;
	//CDibObj* m_pDibObj;
};

}
#endif // WindowAnimation_h__
