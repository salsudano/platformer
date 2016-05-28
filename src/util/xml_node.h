#ifndef __XML_NODE_H
#define __XML_NODE_H

#include <string>
#include <vector>
#include <libxml\xinclude.h>
#include "util\xml_defs.h"
#include "util\xml_attribute.h"

class XMLNode
{
public:
	XMLNode(xmlNode* pNode, bool bKeepTextNodes = false)
	{
		if (pNode != nullptr)
		{
			m_Type = (const char*) pNode->name;

			xmlAttr* pAttr = pNode->properties;
			while (pAttr != nullptr)
			{
				m_lsAttributes.push_back(XMLAttribute(pAttr));
				pAttr = pAttr->next;
			}

			xmlNode* pChildNode = pNode->children;
			while (pChildNode != nullptr)
			{
				XMLNode child(pChildNode);
				if (bKeepTextNodes || !child.IsText())
					m_lsChildren.push_back(child);
				pChildNode = pChildNode->next;
			}
		}
	}

	~XMLNode()
	{
	}

	bool IsText() const
	{
		return (m_Type == XML::Node::Type::Text);
	}

	unsigned int ChildCount() const
	{
		return m_lsChildren.size();
	}

	const XMLNode* GetChild(unsigned int index) const
	{
		if (index < m_lsChildren.size())
			return &(m_lsChildren[index]);
		return nullptr;
	}

	const unsigned int AttributeCount() const
	{
		return m_lsAttributes.size();
	}

	const bool HasAttribute(const std::string& attribute) const
	{
		const auto& iter = std::find_if(m_lsAttributes.begin(), m_lsAttributes.end(), 
			[&](const XMLAttribute& attr) {
				return attr.Description() == attribute;
			});
		return iter != m_lsAttributes.end();
	}

	const XMLAttribute* GetAttribute(unsigned int index) const
	{
		if (index < m_lsAttributes.size())
			return &(m_lsAttributes[index]);
		return nullptr;
	}

	void Type(std::string type) 
	{ 
		m_Type = type;
	}

	const std::string& Type() const 
	{ 
		return m_Type; 
	}

private:
	std::string				  m_Type;
	std::vector<XMLAttribute> m_lsAttributes;
	std::vector<XMLNode>	  m_lsChildren;
};

#endif // __XML_NODE_H