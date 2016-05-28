#ifndef __GAME_H
#define __GAME_H

#include "application.h"

class Game : private Application
{
public:
			Game(const sf::String& name);
		   ~Game();

	int		Run()			override;

private:
	int		ProcessInput()	override;
	int		Update()		override;
	int		Render()		override;

private:
	sf::Clock	m_Timer;
};

#endif // __GAME_H