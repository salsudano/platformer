#include "application_settings.h"

ApplicationSettings::ApplicationSettings(const std::string& title)
	: Title(title)
	, Settings("settings.json")
{
}

ApplicationSettings::~ApplicationSettings() 
{
	SaveSettings();
}

bool ApplicationSettings::SaveSettings()
{
	return true;
}