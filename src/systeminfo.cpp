#include "systeminfo.h"

SystemDisplayInfo::SystemDisplayInfo()
	: CurrentResolution(sf::VideoMode::getDesktopMode())
	, AvailableResolutions(sf::VideoMode::getFullscreenModes())
{
}

SystemDisplayInfo::~SystemDisplayInfo()
{
}

SystemInfo::SystemInfo()
{
}

SystemInfo::~SystemInfo()
{
}
