#ifndef __CONFIG_VALUE_H
#define __CONFIG_VALUE_H

#include <string>
#include <assert.h>

class ConfigValue
{
public:
	enum CFGValueType
	{
		Boolean,
		String,
		Integer
	};

	ConfigValue() 
		: m_bStrIsValid(false)  
		, m_bIntIsValid(false)  
		, m_bBoolIsValid(false)  
		, m_bOptionIsValid(false)
		, m_Type(String)
	{
	}

	ConfigValue(const std::string& option, const std::string& value, const std::string& cfgFile = "")
		: m_Option(option)
		, m_CfgFile(cfgFile)
		, m_bStrIsValid(false)  
		, m_bIntIsValid(false)  
		, m_bBoolIsValid(false)  
		, m_bOptionIsValid(false)
		, m_Type(ConfigValue::ValueType(value))
	{
		SetValue(value);
	}

	bool SetValue(const std::string& value)
	{
		m_bOptionIsValid = (m_Option.length() > 0);
		if (m_bOptionIsValid)
		{
			m_Type = ConfigValue::ValueType(value);
			SetStringVal(value);
			SetBoolVal(value);
			SetIntVal(value);
			return true;
		}
		return false;
	}

	bool SetValue(const int value)
	{
		m_bOptionIsValid = (m_Option.length() > 0);
		if (m_bOptionIsValid)
		{
			m_IntValue = value;
			m_Type = ConfigValue::Integer;
			SetStringVal("");
			SetBoolVal("");
			return true;
		}
		return false;
	}

	bool SetValue(const bool value)
	{
		m_bOptionIsValid = (m_Option.length() > 0);
		if (m_bOptionIsValid)
		{
			m_Type = ConfigValue::Boolean;
			m_BoolValue = value;
			SetStringVal("");
			SetIntVal("");
			return true;
		}
		return false;
	}

	bool BoolValue() const
	{ 
		assert(m_bBoolIsValid);
		return m_BoolValue; 
	}

	int	IntValue() const
	{
		assert(m_bIntIsValid);
		return m_IntValue;
	}

	const std::string& StrValue() const
	{ 
		assert(m_bStrIsValid);
		return m_StrValue;
	}

	const std::string& Option() const
	{ 
		assert(m_bOptionIsValid);
		return m_Option;
	}
	
	const CFGValueType Type() const
	{
		return m_Type;
	}

	bool IsValid() const
	{
		return (m_bOptionIsValid && (m_bStrIsValid || m_bIntIsValid || m_bBoolIsValid));
	}

	static bool IsValidIntegerValue(const std::string& value, int& iValue)
	{
		char* cConversionEnd = '\0';
		int iTemp = strtol(value.c_str(), &cConversionEnd, 10);
		if (cConversionEnd[0] == '\0')
		{
			iValue = iTemp;
			return true;
		}
		return false;
	}

	static bool IsValidBooleanValue(const std::string& value, bool& bValue)
	{
		bool bTrue  = ((value ==  "TRUE") || (value ==  "true") || (value ==  "True"));
		bool bFalse = ((value == "FALSE") || (value == "false") || (value == "False"));
		if (bTrue || bFalse)
		{
			bValue = bTrue;
			return true;
		}
		return false;
	}

	static CFGValueType ValueType(const std::string& value)
	{
		if (value.length() > 0)
		{
			int iDummy = 0;
			bool bDummy = false;
			if (IsValidBooleanValue(value, bDummy))
				return Boolean;
			else if (IsValidIntegerValue(value, iDummy))
				return Integer;
		}
		return String;
	}

private:
	bool SetStringVal(const std::string& value)
	{
		m_StrValue = value;
		m_bStrIsValid = (m_StrValue.length() > 0);
		return m_bStrIsValid;
	}

	bool SetBoolVal(const std::string& value)
	{
		m_bBoolIsValid = ConfigValue::IsValidBooleanValue(value, m_BoolValue);
		return m_bBoolIsValid;
	}

	bool SetIntVal(const std::string& value)
	{
		m_bIntIsValid = ConfigValue::IsValidIntegerValue(value, m_IntValue);
		return m_bIntIsValid;
	}

private:
	int					m_IntValue;
	bool				m_BoolValue;
	std::string			m_StrValue;
	std::string			m_Option;
	std::string			m_CfgFile;
	CFGValueType		m_Type;
	bool				m_bOptionIsValid;
	bool				m_bStrIsValid;
	bool				m_bIntIsValid;
	bool				m_bBoolIsValid;
};

#endif // __CONFIG_VALUE_H
