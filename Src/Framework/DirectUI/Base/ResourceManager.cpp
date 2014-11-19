#include "stdafx.h"
#include "ResourceManager.h"
#include "TinyXml/tinyxml.h"
#include "Base/TemplateObject.h"
#include "Base/UIEngine.h"
#include "Control/ControlUI.h"


CResourceManager * CResourceManager::m_pInstace = NULL;
CUIEngine* CResourceManager::m_pEngine = NULL;  

CResourceManager::CResourceManager(void)
{
	m_DefaultLangID = GetUserDefaultUILanguage();
}


CResourceManager::~CResourceManager(void)
{
	TemplateMap::iterator iter = m_mapLayouts.begin();
	TemplateMap::iterator end = m_mapLayouts.end();
	while (iter != end)
	{
		delete iter->second;
		++iter;
	}

}

CResourceManager * CResourceManager::GetInstance()
{
	if ( m_pInstace == NULL)
	{
		m_pInstace = new CResourceManager;
		m_pEngine = CUIEngine::GetInstance();
	}
	return m_pInstace;
}

void CResourceManager::ReleaseInstance()
{
	if ( m_pInstace != NULL)
	{
		delete m_pInstace;
		m_pInstace = NULL;
	}
}

LANGID CResourceManager::GetLanguage()
{
	return m_DefaultLangID;
}

void CResourceManager::InitResouceDir(LPCTSTR lpszPath,bool bIsDefault /*= false*/)
{
	// 1.���Ŀ¼�Ϸ��ԣ��������һ�� Resource.xml
	CString strResourceFilePath(lpszPath);
	strResourceFilePath+= _T("\\Resource.xml");
	if ( !::PathFileExists(strResourceFilePath) )
	{
		// TODO ������Ҫ�������
		return;
	}
	
	// 2.����Resouce.xml
	// component��Ϊkey���ļ�·����Ϊvalue������m_mapComponent
	// LayoutFiles�У�type��Window/View�ı��浽m_mapLayouts,��Font��ֱ�Ӳ���m_vecFontPool
	// LanguageFiles�У�����ǰ��ʾ���ԣ�����ϵͳ���أ�����m_mapI18NPool
	// TODO �ݲ�֧�� Template�У�ֱ�Ӳ���m_mapTemplates
	TiXmlDocument doc;
	if ( !doc.LoadFile(CDuiCharsetConvert::UnicodeToMbcs(strResourceFilePath).c_str(),TIXML_ENCODING_UTF8))
	{
		return;
	}

	TiXmlElement *pRootElement = doc.RootElement();
	LPCSTR pComponent = pRootElement->Attribute("component");
	if ( pComponent == NULL)
		return;

	CDuiString strComponentName = CDuiCharsetConvert::MbcsToUnicode(pComponent);
	m_mapComponent[strComponentName] = lpszPath;

	TiXmlElement *pLayouts = pRootElement->FirstChildElement("Layouts");
	if ( pLayouts!=NULL)
		parseLayouts(pLayouts, strComponentName.c_str());

	TiXmlElement *pFonts =  pRootElement->FirstChildElement("Fonts");
	if ( pFonts!=NULL)
		parseFonts(pFonts,strComponentName.c_str());

	TiXmlElement *pLanguages =  pRootElement->FirstChildElement("Languages");
	if ( pLanguages!=NULL)
		parseLanguages(pLanguages,strComponentName.c_str());

	// 3.�Ƿ�Ϊ����Դ·��
	if ( bIsDefault )
	{
		m_strDefaultResourcePath = lpszPath;
		// TODO ������Ҫ����һ��Ĭ����Դ·�����֪ͨ
	}
}

TemplateObject* CResourceManager::GetWindowTemplate(LPCTSTR lpszWindowTemplateName)
{
	TemplateMap::iterator iter;
	iter = m_mapLayouts.find(lpszWindowTemplateName);
	if ( iter != m_mapLayouts.end() )
	{
		return iter->second;
	}

	return NULL;
}

TemplateObject* CResourceManager::GetViewTemplate(LPCTSTR lpszViewTemplateName)
{
	return NULL;
}

void CResourceManager::FreeResource(LPCTSTR lpszComponentName)
{
	
}

bool CResourceManager::GetAbsolutePath(CDuiString& strFullPath,LPCTSTR lpszComponent,LPCTSTR lpszRelativePath)
{
	StringMap::iterator iter = m_mapComponent.find(lpszComponent);
	if ( iter != m_mapComponent.end())
	{
		strFullPath = lpszRelativePath;
		CDuiStringOperation::replace(strFullPath,_T("#"),_T("\\"));
		CDuiStringOperation::replace(strFullPath,lpszComponent,(iter->second).c_str());
		return true;
	}
	return false;
}

bool CResourceManager::GetAbsolutePath(CDuiString& strFullPath,LPCTSTR lpszRelativePath)
{
	CDuiString strTemp(lpszRelativePath);
	if ( strTemp.empty())
		return false;

	size_t iIndex = strTemp.find(_T('#'));
	if ( iIndex != strTemp.npos)
	{
		CDuiString strComponent = strTemp.substr(0,iIndex);
		StringMap::iterator iter = m_mapComponent.find(strComponent.c_str());
		if ( iter != m_mapComponent.end())
		{
			strFullPath = lpszRelativePath;
			CDuiStringOperation::replace(strFullPath,_T("#"),_T("\\"));
			CDuiStringOperation::replace(strFullPath,strComponent.c_str(),(iter->second).c_str());
			return true;
		}
	}
	strFullPath = lpszRelativePath;
	return false;
}

void CResourceManager::parseLayouts(TiXmlElement * pLayouts, LPCTSTR lpszComponentName)
{
	TiXmlElement *pElement = pLayouts->FirstChildElement("File");
	do 
	{
		if ( pElement == NULL)
			break;

		do 
		{
			CDuiString strPath;
			CDuiString strName;

			LPCSTR pcstrAttributeVaule = NULL;

			pcstrAttributeVaule = pElement->Attribute("name");
			if ( pcstrAttributeVaule != NULL)
				strName = CDuiCharsetConvert::UTF8ToUnicode(pcstrAttributeVaule);
			else
				break;

			pcstrAttributeVaule = pElement->Attribute("path");
			if ( pcstrAttributeVaule != NULL)
				strPath = CDuiCharsetConvert::UTF8ToUnicode(pcstrAttributeVaule);
			else
				break;

			CDuiString strAbsolutePath;
			GetAbsolutePath(strAbsolutePath,lpszComponentName,strPath.c_str());
			if ( ::PathFileExists(strAbsolutePath.c_str()))
			{

				TemplateObject* pTemplate = this->parseXmlFile(strAbsolutePath.c_str());
				if ( pTemplate )
				{
					m_mapLayouts[strName] = pTemplate;
				}
			}
			
		} while (false);

		pElement = pElement->NextSiblingElement();
	} while (pElement != NULL);
}

void CResourceManager::parseFonts(TiXmlElement * pLayouts, LPCTSTR lpszComponentName)
{
	TiXmlElement *pElement = pLayouts->FirstChildElement("File");
	do 
	{
		if ( pElement == NULL)
			break;



		pElement = pElement->NextSiblingElement();
	} while (pElement != NULL);
}

void CResourceManager::parseLanguages(TiXmlElement * pLayouts, LPCTSTR lpszComponentName)
{
	TiXmlElement *pElement = pLayouts->FirstChildElement("File");
	do 
	{
		if ( pElement == NULL)
			break;

		do 
		{
			LANGID wLangID = 0;
			CDuiString strPath;

			LPCSTR pcstrAttributeVaule = NULL;

			pcstrAttributeVaule = pElement->Attribute("langid");
			if ( pcstrAttributeVaule != NULL)
				wLangID = CDuiCodeOperation::MbcsStrToInt(pcstrAttributeVaule);
			else
				break;

			if ( wLangID != m_DefaultLangID)
				break;

			pcstrAttributeVaule = pElement->Attribute("path");
			if ( pcstrAttributeVaule != NULL)
				strPath = CDuiCharsetConvert::UTF8ToUnicode(pcstrAttributeVaule);
			else
				break;

			CDuiString strAbsolutePath;
			GetAbsolutePath(strAbsolutePath,lpszComponentName,strPath.c_str());
			if ( ::PathFileExists(strAbsolutePath.c_str()))
			{
				this->LoadI18NString(strAbsolutePath.c_str());
			}

		} while (false);

		pElement = pElement->NextSiblingElement();
	} while (pElement != NULL);
}

CControlUI * CResourceManager::CreateControlFromTemplate(TemplateObject *pTemplate,CWindowUI* pManager,CControlUI* pParent/*=NULL*/)
{
	CControlUI* pReturnControl = NULL;
	pReturnControl = m_pEngine->CreateControl(pTemplate->GetType());
	if ( pReturnControl != NULL )
	{
		// �ؼ������ɹ������ù���
		pReturnControl->SetManager(pManager,pParent);

		// ���ÿؼ�����
		AttributeMap::iterator iter = pTemplate->m_mapAttribute.begin();
		AttributeMap::iterator end = pTemplate->m_mapAttribute.end();
		while (iter != end )
		{
			pReturnControl->SetAttribute(iter->first.c_str(),iter->second.c_str());
			++iter;
		}

		// �ṩIContainter�ӿڵĲ��ֿؼ��ż��������������ӿؼ�
		IContainerUI *pContainer = static_cast<IContainerUI*>(pReturnControl->GetInterface(_T("IContainer")));
		int nCount = pTemplate->GetChildCount();
		if ( pContainer != NULL && nCount > 0)
		{
			// ���ӿؼ�
			for (int i=0;i<nCount;++i )
			{
				CControlUI *pChildControl = this->CreateControlFromTemplate(pTemplate->GetChild(i),pManager,pReturnControl);
				if ( pChildControl != NULL)
					pContainer->Add(pChildControl);
			}
		}
	}

	return pReturnControl;
}

TemplateObject* CResourceManager::parseXmlFile(LPCTSTR lpszFilePath)
{	
	TiXmlDocument doc;
	if ( !doc.LoadFile(CDuiCharsetConvert::UnicodeToMbcs(lpszFilePath).c_str(),TIXML_ENCODING_UNKNOWN))
	{
		ASSERT(false);
		return NULL;
	}

	TiXmlElement *pRootElement = doc.RootElement();
	return XmlToTemplate(pRootElement,NULL);
}

TemplateObject* CResourceManager::XmlToTemplate(TiXmlElement *pElement,TemplateObject* pParent)
{
	TemplateObject *pChildTemplateObj = new TemplateObject;
	pChildTemplateObj->SetType(CDuiCharsetConvert::MbcsToUnicode(pElement->Value()).c_str());

	TiXmlAttribute * pAttribute = pElement->FirstAttribute();
	while (pAttribute != NULL)
	{
		
		pChildTemplateObj->SetAttribute(
			CDuiCharsetConvert::UTF8ToUnicode(pAttribute->Name()).c_str(),
			CDuiCharsetConvert::UTF8ToUnicode(pAttribute->Value()).c_str()
			);
		//::OutputDebugStringA(pAttribute->Name());
		//::OutputDebugStringA(pAttribute->Value());
		pAttribute = pAttribute->Next();
	}

	TiXmlElement *pChildElement = pElement->FirstChildElement();
	while (pChildElement != NULL)
	{
		this->XmlToTemplate(pChildElement,pChildTemplateObj);

		pChildElement = pChildElement->NextSiblingElement();
	}

	if ( pParent == NULL)
	{
		return pChildTemplateObj;
	}
	else
	{
		pParent->InsertChild(pChildTemplateObj,0);
	}

	return NULL;
}

LPCTSTR CResourceManager::GetI18N(LPCTSTR lpszName)
{
	StringMap::iterator iter = m_mapI18NCached.find(lpszName);
	if ( iter != m_mapI18NCached.end())
	{
		return iter->second.c_str();
	}

	return NULL;
}

void CResourceManager::SetLanguage(LANGID wLangID)
{
	m_DefaultLangID = wLangID;
}

void CResourceManager::LoadI18NString(LPCTSTR lpszFilePath)
{
	TiXmlDocument doc;
	if ( !doc.LoadFile(CDuiCharsetConvert::UnicodeToMbcs(lpszFilePath).c_str(),TIXML_ENCODING_UTF8))
	{
		return;
	}

	TiXmlElement *pRootElement = doc.RootElement();
	TiXmlElement *pStringElemet = pRootElement->FirstChildElement("String");

	do 
	{
		if ( pStringElemet == NULL)
			break;

		LPCSTR pName = pStringElemet->Attribute("name");
		if ( pName != NULL)
		{
			CDuiString strName = CDuiCharsetConvert::UTF8ToUnicode(pName);

			LPCSTR pVaule = pStringElemet->Value();
			if ( pVaule != NULL)
			{
				m_mapI18NCached[strName] = CDuiCharsetConvert::UTF8ToUnicode(pVaule);
			}
		}

		pStringElemet = pStringElemet->NextSiblingElement();
	} while (pStringElemet != NULL);
}

//ImageObject* CResourceManager::GetImage(LPCTSTR lpszImagePath,bool bCached /*= true */)
//{
//	// ����һ��ͼƬ����
//	// bCachedΪtrue�����ӳټ���ͼƬ�����ɹ��������������ɾ��
//	// ���ص�ImageObjectʵ������ʱ����Release��������Ϊnull
//	// ���棺���ܶԷ��صĶ������delete
//	CDuiString strFullPath;
//	GetAbsolutePath(strFullPath,lpszImagePath);
//	ImageObject *pNewImage = new ImageObject;
//	pNewImage->SetImagePath(strFullPath.c_str());
//}

