#ifndef ScrollBarUI_h__
#define ScrollBarUI_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ScrollBarUI.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2014-11-14 9:20:00
// ˵��			:	������
/////////////////////////////////////////////////////////////*/
#pragma once
class CContainerUI;

class DIRECTUI_API CScrollBarUI
	: public CControlUI
{
public:
	CScrollBarUI(void);
	virtual ~CScrollBarUI(void);
	UI_DECLARE_DYNCREATE();

	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface(LPCTSTR lpszClass);

	CContainerUI* GetOwner() const;
	void SetOwner(CContainerUI* pOwner);

	bool IsHorizontal();
	void SetHorizontal(bool bHorizontal = true);
	int GetScrollRange() const;
	void SetScrollRange(int nRange);
	int GetScrollPos() const;
	void SetScrollPos(int nPos);
	int GetLineSize() const;
	void SetLineSize(int nSize);

private:
	bool m_bHorizontal;
	int m_nRange;
	int m_nScrollPos;
	int m_nLineSize;
	CContainerUI* m_pOwner;
};

#endif // ScrollBarUI_h__
