#ifndef Animation_h__
#define Animation_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	Animation.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2015-05-15 12:50:26
// ˵��			:	����	
/////////////////////////////////////////////////////////////*/
#pragma once

namespace DuiLib
{
	class UILIB_API AlphaChangeAnimation
		: public CAction
{
public:
	AlphaChangeAnimation();
	virtual ~AlphaChangeAnimation();
	void SetKeyFrameAlpha(int startAlpha, int endAlpha);

	virtual LPCTSTR GetClass();

protected:
	virtual void startWithTarget(CObjectUI* pActionTarget);

	virtual void Tick(IActionInterval* pActionInterval);

	virtual void onStop();

	virtual void onFinished();
private:
	int m_nStartAlpha;
	int m_nEndAlpha;
};


class UILIB_API PosChangeAnimation
	: public CAction
{
public:
	PosChangeAnimation();
	void SetKeyFramePos(const RECT* pStartPos, const RECT* pEndPos);

	virtual LPCTSTR GetClass();

protected:
	virtual void startWithTarget( CObjectUI* pActionTarget );

	virtual void Tick( IActionInterval* pActionInterval );

	virtual void onStop();

	virtual void onFinished();

	//CCoordinate m_startCoordinate;
	//CCoordinate m_endCoordinate;
private:
	CDuiRect m_startPos;
	CDuiRect m_stopPos;
};

// ����֡����
class UILIB_API ImageSequenceAnimation
	: public CAction
{
public:
	ImageSequenceAnimation();
	virtual ~ImageSequenceAnimation();

	virtual LPCTSTR GetClass();

protected:
	virtual void startWithTarget( CObjectUI* pActionTarget );

	virtual void Tick( IActionInterval* pActionInterval );

	virtual void onStop();

	virtual void onFinished();
private:

};

//////////////////////////////////////////////////////////////////////////
// ������������
// ��ת�ද������Ҫê��֧��
class UILIB_API TransitionAnimation
	: public CAction
{
public:
	TransitionAnimation();
	virtual LPCTSTR GetClass();

	void BindObj(CControlUI* pOut, CControlUI* pIn);

	CControlUI* GetOut();
	CControlUI* GetIn();

protected:

	virtual void startWithTarget( CObjectUI* pActionTarget );

private:
	CControlUI* m_pOutView;
	CControlUI* m_pInView;
};

// ��ת����
class UILIB_API TurnTransition
	: public TransitionAnimation
{
public:
	TurnTransition();

	virtual LPCTSTR GetClass();

protected:
	virtual void Tick( IActionInterval* pActionInterval );
	virtual void onStop();
	virtual void onFinished();
};

}
#endif // Animation_h__