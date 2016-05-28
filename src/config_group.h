#ifndef __CONFIG_GROUP_H
#define __CONFIG_GROUP_H

#include <string>
#include <vector>

#include "util/t_hash.h"
#include "config_value.h"

class ConfigGroup
{
public:
	ConfigGroup() { }
	ConfigGroup(std::string group) 
		: Group(group) 
	{ }
	ConfigGroup(std::string group, const ConfigValue& value) 
	{
		Group = group;
		Values.push_back(value);
	}

	unsigned int Hash() const
	{
		return THash<ConfigGroup>::StringHashValue(Group);
	}

	bool operator == (const ConfigGroup& r) const
	{
		return (Group == r.Group);
	}

public:
	std::string				 Group;
	std::vector<ConfigValue> Values;
};

#endif // __CONFIG_GROUP_H