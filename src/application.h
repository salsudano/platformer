#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "util/logging.h"
#include "systeminfo.h"
#include "window_event_manager.h"
#include "application_settings.h"
#include "graphics_manager.h"
#include "config_manager.h"

class Application
{
public:
				  Application(const sf::String& name);
	virtual		 ~Application();
	
	virtual int	  Run()			 = 0;

protected:
	virtual int	  ProcessInput() = 0;
	virtual int	  Update()		 = 0;
	virtual int   Render()		 = 0;

	virtual bool  ShouldExit();

protected:
	DataManager*			m_pData;
	sf::RenderWindow		m_MainWindow;
	ApplicationSettings		m_Settings;
	WindowEventManager		m_WindowEventMgr;
	GraphicsManager			m_GraphicsMgr;
	XMLLog					m_Log;
};

#endif // __APPLICATION_H