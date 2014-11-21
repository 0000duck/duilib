#ifndef ComponentUI_h__
#define ComponentUI_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ComponentUI.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2014-11-21 17:08:06
// ˵��			:	��ϲ��֣���Ҫ�����¼�����
/////////////////////////////////////////////////////////////*/
#pragma once
class DIRECTUI_API CComponentUI
	: public CContainerUI
	, public INotifyUI
{
public:
	CComponentUI(void);
	virtual ~CComponentUI(void);
	UI_DECLARE_DYNCREATE();

	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface(LPCTSTR lpszClass);

	// INotifyUI
	virtual bool Notify(TNotifyUI *pMsg);

	void AddNotify(INotifyUI *pNotify);
	void RemoveNotify(INotifyUI *pNotify);

private:
	CStdPtrArray m_arrayNotifyFilters;
};

#endif // ComponentUI_h__
