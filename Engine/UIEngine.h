#ifndef UIEngine_h__
#define UIEngine_h__
#pragma once

namespace DuiLib
{

class CWindowUI;
class CWindowWnd;
//////////////////////////////////////////////////////////////////////////
// CUIEngine
class UILIB_API CUIEngine
	: public IUIEngine
{
public:
	CUIEngine();
	~CUIEngine();
	static CUIEngine* s_pUIEngine;

public:
	static CUIEngine* GetInstance();

public:
	virtual DWORD GetEngineVersion();

	// 1����ʼ�������
	virtual void Init();
	// 2���������ڣ�
	//new CWindowUI()
	// 3����Ϣѭ��
	virtual int  MessageLoop();
	// 4�����ٽ����
	virtual void Uninit();

	// ���ý�����Դ���
	virtual void SetInstanceHandle(HINSTANCE hInstance);
	virtual HINSTANCE GetInstanceHandle();

	virtual HWND GetPumpWnd();

	// ��Ϣ�ýӿ�
	virtual bool TranslateMessage(const LPMSG pMsg);
	virtual bool PumpMessage();

	// ע��/��ע���Ի洰��
	void SkinWindow(CWindowUI* pWindow);
	void UnSkinWindow(CWindowUI* pWindow);

	// ���д���ӿ�
	virtual void AddIdleFilter(IIdleFilter* pFilter);
	virtual void RemoveIdleFilter(IIdleFilter* pFilter);

	// �Ի洰�ڲ���
	virtual int GetWindowCount();
	// ���ݴ��ھ�������Ի洰��
	virtual CWindowUI* GetWindow(HWND hWnd);
	// ���ݴ������Ʋ����Ի洰��
	virtual CWindowUI* GetWindow(LPCTSTR lpszName);
	// ���ݴ������������Ի洰��
	virtual CWindowUI* GetWindow(UINT nIndex);
	// ��ȡ��ǰ���㴰��
	virtual CWindowUI* GetKeyWindow();
	// ���ý��㴰��
	virtual CWindowUI* SetKeyWindow(CWindowUI* pKeyWindow);

	// �ؼ�ע���봴���ӿ�
	virtual void RegisterControl(LPCTSTR lpszType, PROCCONTROLCREATE pFn_ControlCreate);
	virtual void UnregisterControl(LPCTSTR lpszType);
	virtual CControlUI* CreateControl(LPCTSTR lpszType);

	virtual LPCTSTR GetAppDir();
	virtual LPCTSTR GetWorkDir();
	virtual BOOL SetWorkDir(LPCTSTR lpszWorkDir);

private:
	BOOL IsIdleMessage( MSG* pMsg );

private:
	HINSTANCE m_hInstance;
	typedef std::map<CDuiString, PROCCONTROLCREATE> ProcControlCreateMap;
	ProcControlCreateMap m_ControlCreateMap;
	CStdPtrArray m_arrayDirectUI;
	CStdPtrArray m_arrayIdleFilters;
	CDuiString m_strAppDir;
	CWindowUI* m_pKeyWindow;
	CBufferPtr m_strWorkDir;
	CWindowWnd* m_pPumpWnd;
};

}


#endif // UIEngine_h__
