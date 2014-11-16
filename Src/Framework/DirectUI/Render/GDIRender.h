#ifndef GDIRender_h__
#define GDIRender_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	GDIRender.h
// ������		: 	daviyang35@gmail.com
// ����ʱ��	:	2014-11-09 16:49:29
// ˵��			:	GDI Render
/////////////////////////////////////////////////////////////*/
#pragma once
#include "Define/IUIRender.h"

class CGDIRender
	: public IUIRender
{
public:
	CGDIRender(void);
	virtual ~CGDIRender(void);

	virtual void DrawImage(ImageObject* pImageObj, int nAlpha, int x, int y, int nIndex = 0, bool bHole =false);
	virtual void DrawImage(ImageObject* pImageObj, int nAlpha, RECT& rect, int nIndex = 0, bool bHole =false);
	virtual void DrawImage(ImageObject* pImageObj, RECT& rcSrc, RECT& rcDest, int nIndex = 0);

	virtual void DrawColor(LPCRECT rcSrc,DWORD dwColor);

};

#endif // GDIRender_h__
