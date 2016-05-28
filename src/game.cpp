#include "game.h"
#include "data_manager.h"
#include "game_object.h"

// TODO: make these configurable... move to app settings
static const sf::Time MS_PER_UPDATE = sf::seconds(1.0f / 120.0f); // update at 120hz
static const sf::Time MS_PER_RENDER = sf::seconds(1.0f /  60.0f); // render at  60hz

Game::Game(const sf::String& title)
	: Application(title)
{
	m_pData = new DataManager(m_Settings);
	if (m_pData != nullptr)
		m_pData->LoadLevel(GameData::Level::Test, m_MainWindow.getSize());
}

Game::~Game()
{
	m_pData->Unload();
}

int Game::ProcessInput()
{
	sf::Event windowEvent;

	m_pData->ClearWindowEvents();
	while (m_MainWindow.pollEvent(windowEvent))
		m_WindowEventMgr.ProcessWindowEvent(windowEvent, m_MainWindow, m_pData);

	return m_pData->ProcessInput();
}

int Game::Update()
{
	return m_pData->Update();
}

int Game::Render()
{
	m_GraphicsMgr.RenderScene(m_pData);
	return 0;
}

int Game::Run()
{
	int iRet = 0;

	sf::Time timeLag = sf::Time::Zero;
	sf::Time currentTime = sf::Time::Zero;
	sf::Time elapsedTime = sf::Time::Zero;
	sf::Time lastRenderTime = sf::Time::Zero;
	sf::Time previousTime = m_Timer.getElapsedTime();

	while (!ShouldExit())
	{
		currentTime  = m_Timer.getElapsedTime();
		elapsedTime  = currentTime - previousTime;
		previousTime = currentTime;

		timeLag += elapsedTime;

		ProcessInput();

		// we want to update in fixed steps
		while (timeLag >= MS_PER_UPDATE)
		{
			Update();
			timeLag -= MS_PER_UPDATE;
		}

		sf::Time timeSinceLastRender = m_Timer.getElapsedTime() - lastRenderTime;
		if (MS_PER_RENDER > timeSinceLastRender)
			continue;

		lastRenderTime = m_Timer.getElapsedTime();

		Render();
	}

	return iRet;
}
