#ifndef IAction_h__
#define IAction_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	IAction.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2015-05-15 11:59:04
// ˵��			:	�����ӿ�
/////////////////////////////////////////////////////////////*/
#pragma once
#include "Core/ObjectUI.h"

namespace DuiLib
{
	class CAction;

class UILIB_API IActionInterval
{
public:
	//�Ƿ�����ѭ��
	virtual bool  IsLoop() = 0;
	//�Ƿ����÷���
	virtual bool  IsRebound() = 0;
	//�Ƿ�����
	virtual bool  IsReverse() = 0;
	//�Ƿ����
	virtual bool  IsDone() = 0;
	// �Ƿ�����
	virtual bool IsRunning() =0;
	//ÿ֡���
	virtual DWORD GetInterval() = 0;
	//��ǰ֡
	virtual DWORD GetCurFrame() = 0;
	//��֡��
	virtual DWORD GetTotalFrame() = 0;
	// ���õ�ǰ֡
	virtual void SetCurFrame(DWORD dwCurFrame,bool bReverse) =0;
	// ���ò���
	virtual void SetParam(UINT uInterval, UINT uTotalFrame, bool bLoop, bool bRebound , bool bByStep ) =0;
};

class CActionInterval;

class UILIB_API IActionListener
{
public:
	virtual void OnActionStep(CAction* pAction, IActionInterval* pActionInterval){};
	virtual void OnActionStateChanged(CAction* pAction){}
};

class UILIB_API CAction
	: public CObjectUI
{
	friend class CActionManager;
public:
	typedef enum
	{
		ActionState_Ready = 0,		//׼��״̬
		ActionState_Running,			//������
		ActionState_Paused,			//��ͣ
		ActionState_Stop,				//ֹͣ��δ����ʱ��������
		ActionState_Finished,			//����״̬����ִ��������
		ActionState_Unknown = -1,
	}ActionState;

public:
	CAction();
	virtual ~CAction();

	void Paused();
	void Resume();

	/*!
	   \brief    ��ȡ״̬ 
	   \note     const 
	   \return   CAction::ActionState 
	 ************************************/
	CAction::ActionState GetState() const;

	/*!
	   \brief    ���ü���
	   \param    IActionListener * val 
	   \return   void 
	 ************************************/
	void SetActionListener(IActionListener* pActionListener);

	/*!
	   \brief    ����ִ��Ŀ�� 
	   \note     const 
	   \return   BaseObject* 
	 ************************************/
	CObjectUI* ActionTarget() const;

	/*!
	   \brief    ���ö�������ID
	   \param    LPCTSTR val 
	   \note     
			   curve.liner 
			   curve.quad.in 
			   curve.quad.out 
			   curve.quad.inout 
			   curve.cubic.in 
			   curve.cubic.out 
			   curve.cubic.inout 
			   curve.quart.in 
			   curve.quart.out 
			   curve.quart.inout 
			   curve.quint.in 
			   curve.quint.out 
			   curve.quint.inout 
			   curve.sine.in 
			   curve.sine.out 
			   curve.sine.inout 
			   curve.expo.in 
			   curve.expo.out 
			   curve.expo.inout 
			   curve.circ.in 
			   curve.circ.out 
			   curve.circ.inout 
			   curve.back.in 
			   curve.back.out 
			   curve.back.inout 
	   \return   void 
	 ************************************/
	void SetCurveID(LPCTSTR lpszID);

	/*!
	   \brief    ��ȡ����������
	   \return   CurveObj* 
	 ************************************/
	CCurveObject* GetCurveObj();

	/*!
	   \brief    ���ö�������
	   \param    UINT uInterval �������ʱ��
	   \param    UINT uTotalFrame ��֡��
	   \param    bool bLoop �Ƿ�ѭ��
	   \param    bool bRebound �Ƿ񷴵�
	   \param    bool bByStep true:����;false:ʵ��ʱ��
	   \return   void 
	 ************************************/
	void SetParam(UINT uInterval, UINT uTotalFrame, bool bLoop = false, bool bRebound = false, bool bByStep = true);

	/*!
	   \brief    ���õ�ǰ֡
	   \param    DWORD dwCurFrame 
	   \param    bool bReverse ����
	   \return   void 
	 ************************************/
	void SetCurFrame(DWORD dwCurFrame, bool bReverse = false);


	DWORD GetCurFrame();
	DWORD GetTotalFrame();

	bool IsLoop() const;

	bool IsReverse() const;

	void FinishedOfRelease(bool val);

	virtual LPCTSTR GetClass() = 0;

protected:

	virtual void startWithTarget(CObjectUI* pActionTarget);

	//�������������ָ���̬
	virtual void onStop();

	virtual void onFinished();

	void SetState(CAction::ActionState state);

	void ActionTarget(CObjectUI* pTarget);

	// ����֡
	virtual void Tick(IActionInterval* pActionInterval);

	/// ����
	CActionInterval* m_pActionInterval;
private:
	friend class CActionInterval;

	virtual void Update(IActionInterval* pActionInterval);

	/// ״̬
	ActionState m_stateAction;
	/// ��������
	CCurveObject* m_pCurveObj;
	/// ����Ŀ��
	CObjectUI* m_pActionTarget;
	/// ������
	IActionListener* m_pActionListener;

	bool m_bFinishedOfRelease;
};

}
#endif // IAction_h__