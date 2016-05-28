#ifndef __XML_ATTRIBUTE_H
#define __XML_ATTRIBUTE_H

#include <string>
#include <vector>
#include <libxml\xinclude.h>

class XMLAttribute
{
public:
	XMLAttribute(xmlAttr* pAttr)
	{
		if (pAttr != nullptr)
		{
			m_Type = pAttr->atype;
			m_Description = (char*) pAttr->name;

			xmlNode* pValues = pAttr->children;
			while (pValues != nullptr)
			{
				m_lsValues.push_back((char*) pValues->content);
				pValues = pValues->next;
			}
		}
	}

	const std::string& Description() const 
	{
		return m_Description;
	}

	std::string Value(unsigned int index = 0) const 
	{
		if (index < m_lsValues.size())
			return m_lsValues[index];
		return "";
	}
	
	const std::vector<std::string>& ValueList(unsigned int index = 0) const 
	{
		return m_lsValues;
	}

	xmlAttributeType Type() const 
	{ 
		return m_Type;
	}

private:
	xmlAttributeType		 m_Type;
	std::string				 m_Description;
	std::vector<std::string> m_lsValues;
};

#endif // __XML_ATTRIBUTE_H
