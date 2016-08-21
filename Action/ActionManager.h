#ifndef ActionManager_h__
#define ActionManager_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ActionManager.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2015-05-15 11:50:58
// ˵��			:	����������
/////////////////////////////////////////////////////////////*/
#pragma once

namespace DuiLib
{

class UILIB_API CActionManager
{
private:
	CActionManager(void);
	virtual ~CActionManager(void);
	static CActionManager* s_pInstance;

public:
	static CActionManager* GetInstance();
	static void ReleaseInstance();

	void AddAction(CAction* pAction, CControlUI* pView, bool bStopOther = true);
	void AddAction(CAction* pAction, CWindowUI* pWindow, bool bStopOther = true);
	void AddActionPair(CAction* pAction, CObjectUI* pTarget);

	void RemoveAction(CAction* pAction);
	void RemoveActionByTarget(CObjectUI* pTarget, bool bStop = false);
	void RemoveAllActions();

	bool IsAction(CAction* pAction);

private:
	typedef std::multimap<CObjectUI*,CAction*> TargetToActionElementMap;
	typedef std::multimap<CAction*,CObjectUI*> ActionToObjectElementMap;
	TargetToActionElementMap g_mapTargetToActionElement;
	ActionToObjectElementMap g_mapActionToTargetElement;
};

}

#endif // ActionManager_h__
