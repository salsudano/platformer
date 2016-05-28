#ifndef __DATA_MGR_H
#define __DATA_MGR_H

#include <vector>

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "data_defs.h"

class LevelData;
class MenuData;
class ApplicationSettings;

class DataManager
{
public:
			DataManager(const ApplicationSettings& settings);
		   ~DataManager();

	int		ProcessInput();
	int		Update();

	bool	Init();
	bool	LoadLevel(GameData::Level::IDs levelID, const sf::Vector2u& viewSize);
	bool	Unload();

	bool	ClearWindowEvents();
	bool	StoreWindowEvent(const sf::Event& windowEvent);

	LevelData*	GetActiveLevel() const;

public:
	const ApplicationSettings&	m_Settings;

	LevelData*					m_pActiveLevel;
	std::vector<MenuData*>		m_lsMenuData;

	std::map<sf::Event::EventType, std::vector<sf::Event>> m_WindowEvents;
};

#endif // __DATA_MGR_H
