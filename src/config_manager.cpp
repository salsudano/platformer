#include "config_manager.h"

// config singleton
ConfigManager g_ConfigManager;

ConfigManager* GetConfigManager()
{
	return &g_ConfigManager;
}

ConfigManager::ConfigManager()
	: m_pConfigMap(new ConfigMap())
{ 
}

ConfigManager::~ConfigManager() 
{
	if (m_pConfigMap != nullptr)
		delete m_pConfigMap;
	m_pConfigMap = nullptr;
}

bool ConfigManager::GetBoolVal(const std::string& group, const std::string& option) const
{
	bool ret = false;
	if (m_pConfigMap != nullptr)
	{
		const ConfigValue* pValue = m_pConfigMap->Find(group, option);
		assert(pValue != nullptr);
		if (pValue != nullptr)
			ret = pValue->BoolValue();
	}
	return ret;
}

void ConfigManager::SetBoolVal(const std::string& group, const std::string& option, bool value)
{
	if (m_pConfigMap != nullptr)
	{
		ConfigValue* pValue = m_pConfigMap->Find(group, option);
		assert(pValue != nullptr);
		if (pValue != nullptr)
			pValue->SetValue(value);
	}
}

int ConfigManager::GetIntVal(const std::string& group, const std::string& option) const
{
	int ret = 0;
	if (m_pConfigMap != nullptr)
	{
		ConfigValue* pValue = m_pConfigMap->Find(group, option);
		assert(pValue != nullptr);
		if (pValue != nullptr)
			ret = pValue->IntValue();
	}
	return ret;
}

void ConfigManager::SetIntVal(const std::string& group, const std::string& option, int value)
{
		if (m_pConfigMap != nullptr)
	{
		ConfigValue* pValue = m_pConfigMap->Find(group, option);
		assert(pValue != nullptr);
		if (pValue != nullptr)
			pValue->SetValue(value);
	}
}

std::string ConfigManager::GetStrVal(const std::string& group, const std::string& option) const
{
	std::string ret = "";
	if (m_pConfigMap != nullptr)
	{
		ConfigValue* pValue = m_pConfigMap->Find(group, option);
		assert(pValue != nullptr);
		if (pValue != nullptr)
			return pValue->StrValue();
	}
	return ret;
}

void ConfigManager::SetStrVal(const std::string& group, const std::string& option, const std::string& value)
{
	if (m_pConfigMap != nullptr)
	{
		ConfigValue* pValue = m_pConfigMap->Find(group, option);
		assert(pValue != nullptr);
		if (pValue != nullptr)
			pValue->SetValue(value);
	}
}
