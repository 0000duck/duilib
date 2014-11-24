#ifndef ResourceManager_h__
#define ResourceManager_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ResourceManager.h
// ������		: 	daviyang35@gmail.com
// ����ʱ��	:	2014-11-11 17:47:53
// ˵��			:	ȫ����Դ�����������֣����ԣ�����
/////////////////////////////////////////////////////////////*/
#pragma once
class CUIEngine;
class TemplateObject;
class TiXmlElement;
class CWindowUI;

class DIRECTUI_API CResourceManager
{
public:
	static CResourceManager *GetInstance();
	static void ReleaseInstance();

public:
	// ������Դ����
	virtual void InitResouceDir(LPCTSTR lpszPath,bool bIsDefault = false);
	virtual void FreeResource(LPCTSTR lpszComponentName);
	// ��ȡָ��ģ��Ļ�·��
	// ����Ϊnull����Ĭ����Դ��·��
	LPCTSTR GetResouceDir(LPCTSTR lpszModuleName = NULL);

	// ���õ�ǰ��ʾ���ԣ���δʵ������ʱ���֪ͨ
	virtual void SetLanguage(LANGID wLangID);
	// ��ȡ��ǰ��ʾ����
	LANGID GetLanguage();

	// ��Դ���API

	// ��ȡһ������xml
	TemplateObject* GetWindowTemplate(LPCTSTR lpszWindowTemplateName);
	// ��ȡһ������xml
	TemplateObject* GetViewTemplate(LPCTSTR lpszViewTemplateName);
	// ʹ��xmlʵ�����ؼ�
	CControlUI *CreateControlFromTemplate(TemplateObject *pTemplate,CWindowUI* pManager,CControlUI* pParent=NULL);
	// ��ȡͼƬ��Դ�����ȴӻ����в���
	TImageData* GetImage(LPCTSTR lpszImagePath,DWORD dwMask,bool bCached = true );
	// �ͷŻ����ͼƬ��Դ
	void FreeImage(LPCTSTR lpszImagePath);
	// ����һ������
	void AddFont(FontObject *pFont);
	// �Ƴ���������
	void RemoveAllFont();
	// ͨ�����ֲ�ѯ����
	FontObject*	GetFont(LPCTSTR lpszFontName);
	// ��ȡ��ǰ�����ַ���
	LPCTSTR GetI18N(LPCTSTR lpszName);
	// ��������·��ת��Ϊ����·����������#�ָ�����ֱ�ӷ���
	bool GetAbsolutePath(CDuiString& strFullPath,LPCTSTR lpszRelativePath);
private:
	bool GetAbsolutePath(CDuiString& strFullPath,LPCTSTR lpszComponent,LPCTSTR lpszRelativePath);

	void parseLayouts(TiXmlElement * pLayouts, LPCTSTR lpszComponentName);
	void parseFonts(TiXmlElement * pLayouts, LPCTSTR lpszComponentName);
	void parseLanguages(TiXmlElement * pLayouts, LPCTSTR lpszComponentName);

	TemplateObject* parseXmlFile(LPCTSTR lpszFilePath);
	TemplateObject* XmlToTemplate(TiXmlElement *pElement,TemplateObject* pParent);

	void LoadI18NString(LPCTSTR lpszFilePath);
	TImageData* LoadImage(LPCTSTR lpszFilePath,DWORD dwMask);
	void FreeImageData(TImageData* pData);
	void RemoveAllCachedImage();
private:
	// ��Resource.xml�Ļ���
	StringMap m_mapComponent;		// �����Դ·��
	TemplateMap m_mapLayouts;		// ���֣����������ڣ���ͼ
	// TODO �ݲ�֧�� TemplateMap m_mapTemplates;	// �ɸ�����ʽ
	
private:
	LANGID					m_DefaultLangID;	// ��ǰ��ʾ���ԣ�Ĭ��Ϊ�û���ѡ����
	CDuiString				m_strDefaultResourcePath;
	CDuiString				m_strDefaultFont;	// Ĭ������
	// �Ѽ�����Դ�Ļ���
	FontPoolVector		m_vecFontPool;		// �Ѽ��ص�������ʽ����
	StringMap				m_mapI18NCached;		// ������ַ�������
	CStdStringPtrMap	m_mapImageHash; // �ѻ����ͼƬ��Դ
private:
	CResourceManager(void);
	~CResourceManager(void);
	static CResourceManager *m_pInstace;
	static CUIEngine* m_pEngine;
};

#endif // ResourceManager_h__
