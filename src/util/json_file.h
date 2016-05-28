#ifndef __JSON_FILE_H
#define __JSON_FILE_H

#include <string>
#include <iostream>
#include <sstream>
#include <map>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class JsonFile
{
public:
	JsonFile(const std::string& path)
		: m_FilePath(path)
		, m_Depth(0)
	{
		this->Read();
	}

	~JsonFile()
	{
		this->Save();
	}

	void Save()
	{
		m_JSONTree.sort();
		boost::property_tree::write_json(m_FilePath, m_JSONTree);
	}

	template<typename T>
	std::string GetValue(const T& path)
	{
		boost::optional<std::string> val = m_JSONTree.get_optional<std::string>(path);
		if (val)
			return val.value;
		return 
	}

	template <typename T>
	void SetVal(const std::string& path, const T& val)
	{
		m_JSONTree.put<T>(path, val);
	}

	template <typename T>
	void AddVal(const std::string& path, const T& val)
	{
		m_JSONTree.add<T>(path, val);
	}

private:
	void Read()
	{
		try {
			boost::property_tree::read_json(m_FilePath, m_JSONTree);
		} 
		catch (const std::exception& e) {
			std::cout << "Failed to parse: " << m_FilePath << std::endl; e; 
		}
	}

	void Print(boost::property_tree::ptree const& jsonTree)
	{
		m_Depth += 1;
		using boost::property_tree::ptree;
		ptree::const_iterator end = jsonTree.end();
		for (ptree::const_iterator it = jsonTree.begin(); it != end; ++it) 
		{
			const std::string key = it->first;
			boost::property_tree::ptree val = it->second;
			const std::string val_str = val.get_value<std::string>();
			
			for (int i = 0; i < m_Depth; ++i) std::cout << "  ";
			std::cout << key << ": " << val_str << std::endl;

			Print(val);
		}
		m_Depth -= 1;
	}

private:
	int							m_Depth;
	std::string					m_FilePath;
	boost::property_tree::ptree m_JSONTree;

};

#endif // __JSON_FILE_H