#include "stdafx.h"
#include "ResourceManager.h"
#include "TinyXml/tinyxml.h"
#include "Base/TemplateObject.h"
#include "Base/UIEngine.h"
#include "Control/ControlUI.h"


CResourceManager * CResourceManager::m_pInstace = NULL;
CUIEngine* CResourceManager::m_pEngine = NULL;  

CResourceManager::CResourceManager(void)
	: m_DefaultLangID(MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT))
{
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

void CResourceManager::SetLanguage(LPCTSTR lpszLanguage)
{
	m_strDefaultLanguage = lpszLanguage;
	// TODO ������Ҫ����һ�����Ա��֪ͨ
}

LPCTSTR CResourceManager::GetLanguage()
{
	return m_strDefaultLanguage.c_str();
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

}

void CResourceManager::parseLanguages(TiXmlElement * pLayouts, LPCTSTR lpszComponentName)
{

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

