#ifndef __XML_LOG_H
#define __XML_LOG_H

#ifdef _DEBUG
#include <assert.h>
#include <iostream>
#include <fstream>
#endif

class XMLLog
{
public:
	XMLLog(const std::string& name, bool bPrintToScreen = false)
#ifdef _DEBUG
		: m_Indent("")
		, m_Tab("    ")
		, m_Depth(0)
		, m_bPrint(bPrintToScreen)
#endif
	{
#ifdef _DEBUG
		assert(name.length() > 0);
		m_File.open(name + ".xml");
		assert(m_File.is_open());
#endif
	}

	~XMLLog()
	{
#ifdef _DEBUG
		m_File.close();
#endif
	}

	void OpenNode(const std::string& node)
	{
#ifdef _DEBUG
		assert(node.length() > 0);

		if (m_bPrint)
			std::cout << "\n" << m_Indent << "<" << node << ">";

		m_File << "\n" << m_Indent << "<" << node << ">";
		m_lsOpenNodes.push_back(node);
		m_Indent += m_Tab;
		m_Depth++;
#endif
	}

	template<class T>
	void AddAttr(const std::string& attribute, const T& value)
	{
#ifdef _DEBUG
		if (m_bPrint)
			std::cout << "\n" << m_Indent << "<param " << attribute << "=" << value << "/>";
		m_File << "\n" << m_Indent << "<param " << attribute << "=" << value << "/>";
#endif
	}

	void CloseNode()
	{
#ifdef _DEBUG
		assert(m_lsOpenNodes.size() > 0);
		m_Depth--;
		m_Indent = m_Indent.substr(0, m_Indent.length() - m_Tab.length());
		
		if (m_bPrint)
			std::cout << "\n" << m_Indent << "</" << m_lsOpenNodes.back() << ">";
		m_File << "\n" << m_Indent << "</" << m_lsOpenNodes.back() << ">";
		
		m_lsOpenNodes.pop_back();
#endif
	}

private:
#ifdef _DEBUG
	bool						m_bPrint;
	int							m_Depth;
	std::ofstream				m_File;
	std::string					m_Indent;
	std::string					m_Tab;
	std::vector<std::string>	m_lsOpenNodes;
#endif
};


#endif // __XML_LOG_H