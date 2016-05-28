#ifndef __APPLICATION_OPTIONS_H
#define __APPLICATION_OPTIONS_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "util\json_file.h"

#include "systeminfo.h"

class DebugSettings
{
public:
	DebugSettings()
	{
	}

private:
	bool	m_DebugSettings;
	bool	m_LevelData;
};

class DisplaySettings
{
public:
		DisplaySettings()
			: m_bMouseCursorVisible(true)
			, m_bFullscreenEnabled(false)
			, m_bVerticalSyncEnabled(true)
			, m_uiFramerateLimit(UINT_MAX)
			, m_vmResolution(sf::VideoMode(800, 600, 32))
		{ }

		bool				  FullScreenEnabled() const			{ return m_bFullscreenEnabled; }
		void				  FullScreenEnabled(bool enabled)	{ m_bFullscreenEnabled = enabled; }

		bool				  VerticalSyncEnabled()	const		{ return m_bVerticalSyncEnabled; }
		void				  VerticalSyncEnabled(bool enabled)	{ m_bVerticalSyncEnabled = enabled; }

		bool				  MouseCursorVisible() const		{ return m_bMouseCursorVisible; }
		void				  MouseCursorVisible(bool visible)	{ m_bMouseCursorVisible = visible; }

		unsigned int		  FramerateLimit() const					{ return m_uiFramerateLimit; }
		void				  FramerateLimit(unsigned int frameLimit)	{ m_uiFramerateLimit = frameLimit; }

		const sf::VideoMode&  Resolution()			const			{ return m_vmResolution; }
		void				  Resolution(const sf::VideoMode& res)	{ m_vmResolution = res; }

protected:
	bool			m_bFullscreenEnabled;
	bool			m_bVerticalSyncEnabled;
	bool			m_bMouseCursorVisible;
	unsigned int	m_uiFramerateLimit;
	sf::VideoMode	m_vmResolution;
};

const unsigned int VOLUME_MAX = 100;
const unsigned int VOLUME_MIN = 0;

class AudioSettings
{
public:
		AudioSettings()
			: uiVolume(VOLUME_MAX)
		{}

public:
	unsigned int uiVolume;
};

class ApplicationSettings
{
public:
			ApplicationSettings(const std::string& title);
		   ~ApplicationSettings();

	bool	SaveSettings();

public:
	sf::String		Title;
	SystemInfo		SystemInfo;
	DisplaySettings	Display;
	AudioSettings	Audio;

private:
	JsonFile		Settings;
};

#endif // __APPLICATION_OPTIONS_H
