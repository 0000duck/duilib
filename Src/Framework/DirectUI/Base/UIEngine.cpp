#include "stdafx.h"
#include "UIEngine.h"
#include "Base/ResourceManager.h"

#include "Control/ControlUI.h"
#include "Layout/ContainerUI.h"
#include "Control/ButtonUI.h"

CUIEngine* CUIEngine::m_pUIEngineInstance = NULL;

CUIEngine::CUIEngine(void)
	: m_hInstace(NULL)
	, m_bInitedCOM(false)
	, m_bInitedOLE(false)
	, m_pResourceManager(NULL)
{
}

CUIEngine::CUIEngine(const CUIEngine* rhs)
{

}


CUIEngine::~CUIEngine(void)
{
}

CUIEngine* CUIEngine::GetInstance()
{
	if ( m_pUIEngineInstance == NULL)
	{
		m_pUIEngineInstance = new CUIEngine;
	}
	return m_pUIEngineInstance;
}

void CUIEngine::ReleaseInstance()
{
	if ( m_pUIEngineInstance != NULL)
	{
		delete m_pUIEngineInstance;
		m_pUIEngineInstance = NULL;
	}
}

void CUIEngine::Init()
{
	// ע������ϵͳ�����ؼ�
	this->InitCOM();
	this->InitOLE();
	m_pResourceManager = CResourceManager::GetInstance();
	UI_REGISTER_DYNCREATE(_T("Control"),CControlUI);
	UI_REGISTER_DYNCREATE(_T("Container"),CContainerUI);
	UI_REGISTER_DYNCREATE(_T("ScrollBar"),CScrollBarUI);
	UI_REGISTER_DYNCREATE(_T("Button"),CButtonUI);
}

void CUIEngine::Uninit()
{
	m_pResourceManager = NULL;
	CResourceManager::ReleaseInstance();

	m_ControlCreateMap.clear();
	m_arrayDirectUI.Empty();

	if ( m_bInitedCOM )
	{
		::CoUninitialize();
		m_bInitedCOM = false;
	}
	if ( m_bInitedOLE)
	{
		::OleUninitialize();
		m_bInitedOLE = false;
	}
}

void CUIEngine::SetInstanceHandler(HINSTANCE hInstance)
{
	m_hInstace = hInstance;
}

HINSTANCE CUIEngine::GetInstanceHandler()
{
	return m_hInstace;
}

int CUIEngine::MessageLoop()
{
	MSG msg = { 0 };
	while( ::GetMessage(&msg, NULL, 0, 0) )
	{
		if( !this->TranslateMessage(&msg) )
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	return msg.lParam;
}

bool CUIEngine::TranslateMessage(const LPMSG pMsg)
{
	// pMsg->hwnd ����� m_arrayDirectUI ��
	// ˵������������Ի洰�ڣ��ַ���Ϣ����
	int nCount = m_arrayDirectUI.GetSize();
	if ( !::IsWindow(pMsg->hwnd) )
		return false;

	// ����Ϣ��������ʵ����ʹ����ʵ���л��������Ϣ������ټ�
	LRESULT lRes = S_OK;
	for ( int i=0; i<nCount;++i )
	{
		CWindowUI* pWindow = static_cast<CWindowUI*>(m_arrayDirectUI.GetAt(i));
		if ( pMsg->hwnd != pWindow->GetHWND())
			continue;

		if ( pWindow->TranslateAccelerator(pMsg))
			return true;

		if ( pWindow->PreMessageHandler(pMsg,lRes))
			return true;
	}

	return false;
}

bool CUIEngine::PumpMessage()
{
	MSG msg = { 0 };
	if ( ::GetMessage(&msg,0,0,0) )
	{
		if ( !this->TranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		return true;
	}
	return false;
}

void CUIEngine::InitCOM()
{
	if ( !m_bInitedCOM )
	{
		::CoInitialize(NULL);
		m_bInitedCOM = true;
	}
}

void CUIEngine::InitCOMEx(DWORD dwCoInit)
{
	if ( !m_bInitedCOM )
	{
		::CoInitializeEx(NULL,dwCoInit);
		m_bInitedCOM = true;
	}
}

void CUIEngine::InitOLE()
{
	if ( !m_bInitedOLE )
	{
		::OleInitialize(NULL);
		m_bInitedOLE = true;
	}
}

void CUIEngine::RegisterControl(LPCTSTR lpszType, PROCCONTROLCREATE pFn_ControlCreate)
{
	if ( pFn_ControlCreate == NULL)
		return ;

	ProcControlCreateMap::iterator iter = m_ControlCreateMap.find(lpszType);
	if ( iter == m_ControlCreateMap.end() )
	{
		m_ControlCreateMap[lpszType] = pFn_ControlCreate;
	}
	else
	{
		// Exist Control Type Name
	}
}

CControlUI* CUIEngine::CreateControl(LPCTSTR lpszType)
{
	ProcControlCreateMap::iterator iter = m_ControlCreateMap.find(lpszType);
	if ( iter != m_ControlCreateMap.end())
	{
		PROCCONTROLCREATE pFn_ControlCreate = iter->second;
		return pFn_ControlCreate();
	}
	return NULL;
}

void CUIEngine::UnregisterControl(LPCTSTR lpszType)
{
	ProcControlCreateMap::iterator iter = m_ControlCreateMap.find(lpszType);
	if ( iter != m_ControlCreateMap.end())
	{
		m_ControlCreateMap.erase(iter);
	}
}

void CUIEngine::SkinWindow(CWindowUI* pWindow)
{
	m_arrayDirectUI.Add(pWindow);
}

void CUIEngine::UnSkinWindow(CWindowUI* pWindow)
{
	m_arrayDirectUI.Remove(m_arrayDirectUI.Find(pWindow));
}

CResourceManager* CUIEngine::GetResourceManager()
{
	return m_pResourceManager;
}

CWindowUI* CUIEngine::GetWindow(HWND hWnd)
{
	int count = m_arrayDirectUI.GetSize();
	for (int i = 0; i < count; ++i)
	{
		CWindowUI* pWindow = static_cast<CWindowUI*>(m_arrayDirectUI.GetAt(i));
		HWND hWindow = pWindow->GetHWND();
		if ( ::IsWindow(hWindow) && hWnd == hWindow)
		{
			return pWindow;
		}
	}
	return NULL;
}

CWindowUI* CUIEngine::GetWindow(LPCTSTR lpszName)
{
	int count = m_arrayDirectUI.GetSize();
	for (int i = 0; i < count; ++i)
	{
		CWindowUI* pWindow = static_cast<CWindowUI*>(m_arrayDirectUI.GetAt(i));
		if ( ::IsWindow(pWindow->GetHWND()) )
		{
			if ( _tcscmp(pWindow->GetName(),lpszName) == 0)
				return pWindow;
		}
	}
	return NULL;
}

