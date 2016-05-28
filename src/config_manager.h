#ifndef __CONFIG_MANAGER_H
#define __CONFIG_MANAGER_H

#include <string>

#include "config_group.h"
#include "config_value.h"
#include "config_writer.h"
#include "config_map.h"

class ConfigManager
{
public:
					ConfigManager();
				   ~ConfigManager();

		bool		 GetBoolVal(const std::string& group, const std::string& option) const;
		void		 SetBoolVal(const std::string& group, const std::string& option, bool value);

		int			 GetIntVal(const std::string& group, const std::string& option) const;
		void		 SetIntVal(const std::string& group, const std::string& option, int value);

		std::string	 GetStrVal(const std::string& group, const std::string& option) const;
		void		 SetStrVal(const std::string& group, const std::string& option, const std::string& value);

private:
	void ConfigManager::SetDefaultValues();

private:
	ConfigMap* m_pConfigMap;
};

// Singleton fetcher
ConfigManager* GetConfigManager();

#endif // __CONFIG_MANAGER_H