#ifndef __SYSTEM_INFORMATION_H
#define __SYSTEM_INFORMATION_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class SystemDisplayInfo
{
public:
		SystemDisplayInfo();
	   ~SystemDisplayInfo();

public:
	sf::VideoMode				CurrentResolution;
	std::vector<sf::VideoMode>	AvailableResolutions;
};

class SystemInfo
{
public:
		SystemInfo();
	   ~SystemInfo();
	
public:
	SystemDisplayInfo Display;
};

#endif // __SYSTEM_INFORMATION_H
