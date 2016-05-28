#ifndef __WINDOW_EVENT_MANAGER_H
#define __WINDOW_EVENT_MANAGER_H

#include <SFML\Window.hpp>

class DataManager;

class WindowEventManager
{
public:
			WindowEventManager();
		   ~WindowEventManager();

	bool	ProcessWindowEvent(const sf::Event& windowEvent, sf::Window& window, DataManager* pData);

private:
	bool	HandleWindowClosed(const sf::Event& inputEvent, sf::Window& window);
	bool	HandleWindowResized(const sf::Event& inputEvent, sf::Window& window, DataManager* pData);
	bool	HandleWindowLostFocus(const sf::Event& inputEvent, sf::Window& window);
	bool	HandleWindowGainedFocus(const sf::Event& inputEvent, sf::Window& window);
};

#endif // __WINDOW_EVENT_MANAGER_H
