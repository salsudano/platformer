#include "window_event_manager.h"
#include "data_manager.h"
#include "level_data.h"

WindowEventManager::WindowEventManager()
{
}

WindowEventManager::~WindowEventManager()
{
}

bool WindowEventManager::ProcessWindowEvent(const sf::Event& windowEvent, sf::Window& window, DataManager* pData)
{
	bool ret = false;

	switch (windowEvent.type)
	{
		case sf::Event::Closed:
			ret = HandleWindowClosed(windowEvent, window);
			break;
		case sf::Event::Resized: 
			ret = HandleWindowResized(windowEvent, window, pData);
			break;
		case sf::Event::LostFocus:
			ret = HandleWindowLostFocus(windowEvent, window);
			break;
		case sf::Event::GainedFocus:
			ret = HandleWindowGainedFocus(windowEvent, window);
			break;
	}

	if (ret && pData != nullptr)
		ret = pData->StoreWindowEvent(windowEvent);

	return ret;
}

bool WindowEventManager::HandleWindowClosed(const sf::Event& windowEvent, sf::Window& window)
{
	// no data
	window.close();
	return true;
}

bool WindowEventManager::HandleWindowResized(const sf::Event& windowEvent, sf::Window& window, DataManager* pData)
{
	// data in event.size
	LevelData* pLevelData = pData->GetActiveLevel();
	if (pLevelData != nullptr)
	{
		// TODO: see if this is necessary
		//pLevelData->ResizeViewport(static_cast<float>(window.getSize().x), 
		//						     static_cast<float>(window.getSize().y));
	}
	return true;
}

bool WindowEventManager::HandleWindowLostFocus(const sf::Event& windowEvent, sf::Window& window)
{
	// no data
	return true;
}

bool WindowEventManager::HandleWindowGainedFocus(const sf::Event& windowEvent, sf::Window& window)
{
	// no data
	return true;
}
