#ifndef __CONFIG_WRITER_H
#define __CONFIG_WRITER_H

#include <string>
#include <fstream>

#include "util/t_iterator.h"
#include "config_group.h"

class ConfigWriter : public TIterator<ConfigGroup>
{
public:
	ConfigWriter(const std::string& cfgFilePath)
	{
		m_fhCfgFile.open(cfgFilePath);
	}

	~ConfigWriter() 
	{
		m_fhCfgFile.close();
	}

	void Do(const ConfigGroup& group)
	{
		if (m_fhCfgFile.good())
		{
			// [Group]
			m_fhCfgFile << "[" << group.Group << "]" << std::endl;
			for (unsigned int i = 0; i < group.Values.size(); ++i)
			{
				const ConfigValue& value = group.Values[i];
				// "Option"=
				m_fhCfgFile << "\"" << value.Option() << "\"=";
				switch (value.Type())
				{
					case ConfigValue::Boolean:
						m_fhCfgFile << (value.BoolValue() ? "true" : "false") << std::endl;
						break;
					case ConfigValue::Integer:
						m_fhCfgFile << value.IntValue() << std::endl;
						break;
					case ConfigValue::String:
						m_fhCfgFile << "\"" << value.StrValue() << "\"" << std::endl;
						break;
				}
			}
			m_fhCfgFile << std::endl;
		}
	}

private:
	std::ofstream m_fhCfgFile;
};

#endif // __CONFIG_WRITER_H