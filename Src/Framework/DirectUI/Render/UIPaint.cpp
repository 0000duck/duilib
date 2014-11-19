#include "stdafx.h"
#include "UIPaint.h"


CUIPaint* CUIPaint::m_pInstance = NULL;

CUIPaint::CUIPaint(void)
{
}


CUIPaint::~CUIPaint(void)
{
}

CUIPaint* CUIPaint::GetInstance()
{
	if ( m_pInstance == NULL )
	{
		m_pInstance = new CUIPaint;
	}
	return m_pInstance;
}

void CUIPaint::ReleaseInstance()
{
	if ( m_pInstance != NULL )
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CUIPaint::DrawButton(IUIRender *pRender,CButtonUI *pButton,LPCRECT rcDst)
{
	if ( pButton->CheckState(UISTATE_Disabled))
	{
		// ����״̬��������ͼƬ
		int i=0;
	}
	if ( pButton->CheckState( UISTATE_Pushed) )
	{
		// ����״̬�������㱳���ٻ�����ǰ��
		int i=0;
	}
	if ( pButton->CheckState(UISTATE_Focused))
	{
		int i=0;
	}
	if ( pButton->CheckState(UISTATE_Hover))
	{
		int i=0;
	}
	if ( pButton->CheckState(UISTATE_Normal))
	{
		int i=0;
	}
}
