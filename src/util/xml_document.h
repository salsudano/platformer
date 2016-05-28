#ifndef __XML_DOCUMENT_H
#define __XML_DOCUMENT_H

#include <string>
#include <vector>
#include <libxml\xinclude.h>
#include <util\xml_node.h>

class XMLDocument
{
public:
	XMLDocument(std::string path, bool bKeepTextNodes = false)
	{
		xmlDoc* pXMLDocument = xmlParseFile(path.c_str());
		if (pXMLDocument != nullptr) 
		{
			m_Version  = (char*) pXMLDocument->version;
			m_Encoding = (char*) pXMLDocument->encoding;
			m_Path	   = (char*) pXMLDocument->URL;

			xmlNode* pCurrNode = xmlDocGetRootElement(pXMLDocument);	
			if (pCurrNode == nullptr)
				xmlFreeDoc(pXMLDocument);
			else
			{
				while (pCurrNode != nullptr)
				{
					XMLNode node(pCurrNode, bKeepTextNodes);
					if (bKeepTextNodes || !node.IsText())
						m_lsRootData.push_back(node);
					pCurrNode = pCurrNode->next;
				}
			}
		}
	}

	~XMLDocument()
	{
	}

	bool HasData() const
	{
		return (m_lsRootData.size() > 0);
	}

	bool IsSVGFile() const
	{
		const XMLNode* pRootNode = RootNode();
		return ((pRootNode != nullptr) && (pRootNode->Type() == XML::Node::Type::SVG));
	}

	const XMLNode* RootNode(unsigned int ind = 0) const
	{
		if (HasData() && (ind < Count()))
			return &(m_lsRootData[ind]);
		return nullptr;
	}

	const unsigned int Count() const 
	{
		return m_lsRootData.size();
	}

	const std::string& Version() const  
	{
		return m_Version;
	}

	const std::string& Encoding() const
	{
		return m_Encoding;
	}

	const std::string& Path() const
	{
		return m_Path;
	}

private:
	std::vector<XMLNode>	m_lsRootData;
	std::string				m_Version;
	std::string				m_Encoding;
	std::string				m_Path;
};

#endif // __XML_DOCUMENT_H