#ifndef __GRAPHICS_MANAGER_H
#define __GRAPHICS_MANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class DataManager;

class GraphicsManager
{
public:
			GraphicsManager(sf::RenderWindow& rMainWindow);
		   ~GraphicsManager();

	bool	RenderScene(const DataManager* pGameData);

private:
	sf::RenderWindow&	m_rWindow;
	bool				m_bDrawDebugInfo;
};

#endif // __GRAPHICS_MANAGER_H