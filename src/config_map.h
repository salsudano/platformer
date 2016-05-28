#ifndef __CONFIG_MAP_H
#define __CONFIG_MAP_H

#include <string>
#include <algorithm>

#include "config_group.h"
#include "config_writer.h"

class ConfigMap
{
public:
	ConfigMap()
		: m_ConfigGroupHash(100)
		, m_bSaveOnExit(true)
	{
		ParseConfigFile("C:/Users/Sal/Documents/Programming/trunk_test/projects/vs_output/engine/Debug/object.cfg");
		ParseConfigFile("C:/Users/Sal/Documents/Programming/trunk_test/projects/vs_output/engine/Debug/level.cfg");
	}

	~ConfigMap() 
	{
		if (m_bSaveOnExit)
			SaveConfigFile();
	}

	ConfigValue* Find(const std::string& group, const std::string& option) const
	{
		ConfigValue* pRet = nullptr;
		ConfigGroup* pGroup = m_ConfigGroupHash.Find(group);
		if (pGroup != nullptr)
		{
			for (unsigned int i = 0; ((i < pGroup->Values.size()) && (pRet == nullptr)); ++i)
			{
				ConfigValue* pVal = &(pGroup->Values[i]);
				if (pVal->Option() == option)
					pRet = pVal;
			}
		}
		return pRet;
	}

	bool SetValue(const ConfigGroup& group, const ConfigValue& value)
	{
		return SetValue(group.Group, value.Option(), value.StrValue());
	}

	bool SetValue(const std::string& group, const std::string& option, const std::string& value)
	{
		bool ret = false;
		ConfigGroup cfgGroup(group);
		ConfigValue cfgValue(option, value);
		ConfigGroup* pGroup = m_ConfigGroupHash.Find(cfgGroup);
		if (pGroup != nullptr)
		{
			// Group exists in hash
			bool bFound = false;
			for (unsigned int i = 0; i < pGroup->Values.size() && !bFound; ++i)
			{
				ConfigValue& rVal = pGroup->Values[i];
				if (rVal.Option() == option)
				{
					bFound = true;
					ret = rVal.SetValue(value);
				}
			}
			if (!bFound)
			{
				// option doesn't exist in group yet
				pGroup->Values.push_back(cfgValue);
				ret = true;
			}
		}
		else
		{
			// Group doesn't exist in hash... add it
			cfgGroup.Values.push_back(cfgValue);
			m_ConfigGroupHash.Add(cfgGroup);
			ret = true;
		}
		return ret;
	}

	bool SaveConfigFile()
	{
		ConfigWriter cfgWriter(m_FilePath);
		m_ConfigGroupHash.Iterate(dynamic_cast<TIterator<ConfigGroup>*>(&cfgWriter));
		return false;
	}

private:
	void ParseConfigFile(const std::string& cfgPath)
	{
		std::ifstream fhConfigFile(cfgPath);
		if (fhConfigFile.good() && fhConfigFile.is_open())
		{
			std::string line;
			std::string group;
			std::string option;
			std::string value;
			/*
			while (std::getline(fhConfigFile, line) != false)
			{
				int iEqualsInd = line.find("=");
				int iLBracketInd = line.find("[");
				int iRBracketInd = line.find("]");

				// Config group definition [GroupName]
				if ((iLBracketInd == 0) && (iRBracketInd != std::string::npos))
				{
					group = line.substr(iLBracketInd + 1, iRBracketInd - iLBracketInd - 1);
					ConfigGroup currGroup(group);
					const ConfigGroup* pGroup = m_ConfigGroupHash.Find(currGroup);
					if (pGroup == nullptr)
						m_ConfigGroupHash.Add(currGroup);
				}
				// Config value definitions "Option"="Value" or "Option"=1234 (within the current group)
				else if ((group.length() > 0) && (iEqualsInd != std::string::npos))
				{
					option = line.substr(0, iEqualsInd);
					value  = line.substr(iEqualsInd + 1, line.length() - iEqualsInd + 1);
					if ((option.length() > 0) && (option.length() > 0))
					{
						// If the option label is wrapped in quotes, remove them. If it's not in quotes, it's invalid.
						option = ((option[0] == '\"') && (option[option.length() - 1] == '\"')) ? option.substr(1, option.length() - 2) : "";
						value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());

						ConfigValue cfgValue(option, value);
						if (cfgValue.IsValid())
						{
							ConfigGroup* pGroup = m_ConfigGroupHash.Find(group);
							assert(pGroup != nullptr);
							pGroup->Values.push_back(cfgValue);
						}
					}
				}
			}
			*/
		}
		else
			printf("Config file: %s not found!\n", cfgPath.c_str());

		fhConfigFile.close();
	}

public:
	bool			   m_bSaveOnExit;
	std::string		   m_FilePath;
	THash<ConfigGroup> m_ConfigGroupHash;
};

#endif // __CONFIG_MAP_H