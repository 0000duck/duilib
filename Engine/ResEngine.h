#ifndef ResEngine_h__
#define ResEngine_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ResEngine.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2015-04-24 14:05:00
// ˵��			:	UI��Դ�������������ڣ����ʻ��ַ�����ͼƬ������
/////////////////////////////////////////////////////////////*/
#pragma once
#include "Xml/pugixml.hpp"

namespace DuiLib
{

class UILIB_API CResEngine
	: public IResEngine
	, public IIdleFilter		// ResEngineע��ִ��GC�ռ�
{
private:
	CResEngine(void);
	~CResEngine(void);

	static CResEngine* s_pResEngine;
public:
	static CResEngine* GetInstance();
	static void ReleaseInstance();

public:
	// IResEngine
	virtual void SetLanguage(LPCTSTR lpszLanguage);
	virtual LPCTSTR GetLanguage();

	virtual void SetDefaultFontID(LPCTSTR lpszDefaultFontID);

	virtual void LoadResFromPath(LPCTSTR lpszResPath,bool bDefaultSkin= false);
	virtual void LoadResFromRDB(LPCTSTR lpszRDBPath,bool bDefaultSkin= false);
	virtual void LoadResFromRes(UINT nResID,LPCTSTR lpszResType,bool bDefaultSkin= false);

	virtual void FreeResPackage(LPCTSTR lpszPackageName);

	virtual LPCTSTR GetResDir(LPCTSTR lpszPackageName);

	virtual TImageData* GetImage(LPCTSTR lpszImagePath,DWORD dwMask,bool bCached = true );
	// ��ȡͼƬ��Դ
	TImageData* GetImage(LPCTSTR lpszImageName,bool bCached = true);

	virtual void AddFont(FontObject* pFontObject);
	virtual FontObject* GetFont(LPCTSTR lpszFontID);
	virtual FontObject* GetDefaultFont();

	virtual LPCTSTR GetFont(LPCTSTR pstrFace, int nSize,
		bool bBold=false, bool bUnderline=false, bool bItalic=false,bool bStrikeout=false);
	
	virtual LPCTSTR GetI18NString(LPCTSTR lpszID);

	virtual bool ApplyResTemplate(CControlUI* pControl,LPCTSTR lpszTemplateID);

	virtual void GetHSL(short* H, short* S, short* L);
	// H:0~360, S:0~200, L:0~200 
	virtual void SetHSL(bool bUseHSL, short H, short S, short L);

	virtual DWORD GetDefaultColor(LPCTSTR lpszID);

	virtual CCurveObject* GetCurveObj(LPCTSTR lpszID);

	// �� "{@IDSTRING}" �е�IDSTRING��ΪI18N�ַ���ID��ѯ
	// ͨ�����÷�����ʵ�ַ���
	void ProcessString(CDuiString& strText,LPCTSTR lpszText);
public:
	void SetDefaultShadowImage(LPCTSTR lpszShadowString);
	LPCTSTR GetDefaultShadowImage();

	// ����Ӧ��Ĭ����Ӱ�߾�
	void SetDefaultShadowCorner(LPCRECT lprcCorner);
	RECT GetDefaultShadowCorner();

	// ����Ӧ��Ĭ�ϱ߿�Բ��
	void SetDefaultShadowRoundCorner(LPSIZE lpszRoundCorner);
	SIZE GetDefaultShadowRoundCorner();

public:	// �ڲ�����
	// ����-������������

	// ʹ��ָ��ģ���ʼ�����봰��
	bool CreateWindowWithTemplate(CWindowUI* pWindow,LPCTSTR lpszWindowTemplate);
	// ʹ��ָ��ģ���ʼ���Զ����ֻ�ؼ�
	CControlUI* CreateViewWithTemplate(CControlUI* pParent,LPCTSTR lpszViewTemplate,CControlUI* pNext = NULL);

	TemplateObject* GetTemplate(LPCTSTR lpszWindowTemplateName);

	CControlUI *CreateControlFromTemplate(TemplateObject *pTemplate,CWindowUI* pManager,CControlUI* pParent=NULL);

public:	// ������Դ�������
	// �ͷ�ָ��ͼƬ��Դ
	void RemoveImageFromCache(LPCTSTR lpszImageName);

	void FreeImageData(TImageData* pData);
	void RemoveAllCachedImage();
	void RemoveAllCachedFont();
	void RemoveAllCachedRDB();
	void RemoveCachedTemplate();
	void RemoveCahcedI18N();
	void RemoveCachedStyle();
	void RemoveCurveObj();

private:	
	// ������ԴURI�����ļ�����ȡ
	bool GetRes(CBufferPtr &dataBuffer,LPCTSTR lpszRelative);
	void CrackResXml(pugi::xml_node &root);
	void InitBezierPoint();
	void InsertCurveObj(CCurveObject* pObj,LPCTSTR lpszID);
private:
	TemplateObject* XmlToTemplate(pugi::xml_node& node,TemplateObject* pParent);
	FontObject* XmlToFontObj(pugi::xml_node& font);
	int TemplateToI18N(TemplateObject* pI18NTemplate);
	TemplateObject* XmlToStyleObj(pugi::xml_node& style);

	// GC�����߼�
	virtual void OnIdle();
	void GCImageData();

private:
	FontObject* m_pDefaultFont;
	CDuiString m_strDefaultLanguage;
	CDuiString m_strDefaultSkinPath;
	IResDecoder * m_pResDecoder;

	DWORD m_dwLastGC;

	short m_H;
	short m_S;
	short m_L;

	CDuiString m_strDefaultShadowImage;
	CDuiRect m_rcDefaultShadowCorner;
	CDuiSize m_szDefaultShadowRoundCorner;

	StringMap m_mapSkinPackage;		// Ƥ����·���б�
	TemplateMap m_mapLayouts;		// ���֣����������ڣ���ͼ
	CStdStringPtrMap m_mapFonts;		// ����������

	typedef std::multimap<CDuiString,TemplateObject*> StringTemplateMap;
	// ID->Template*
	StringTemplateMap m_mapI18N;	// I18N���е�Template

	// ID->String
	StringMap		m_mapI18NCached;		// ������ַ�������

	// ID->TImageData*
	CStdStringPtrMap	m_mapImageCache; // �ѻ����ͼƬ��Դ

	// ID->PSkinRDB
	CStdStringPtrMap	m_mapRDB;					// �ѻ���RDB����Դ

	// ID->Style(Template*)
	CStdStringPtrMap m_mapStyle;				// ��ʽ��

	// ID->CCurveObject*
	CStdStringPtrMap m_mapCurvesTable;	// ���߶����
};

}
#endif // ResEngine_h__
