#include "util/t_rect.h"
#include "util/svg_data.h"
#include "util/svg_element.h"

#include "data_manager.h"
#include "menu_data.h"
#include "level_data.h"
#include "application_settings.h"

#include "character_object.h"
#include "inactive_object.h"
#include "interactive_object.h"

DataManager::DataManager(const ApplicationSettings& settings)
	: m_pActiveLevel(nullptr)
	, m_Settings(settings)
{
	Init();
}

DataManager::~DataManager()
{
}

bool DataManager::Init()
{
	return true;
}

bool DataManager::LoadLevel(GameData::Level::IDs levelID, const sf::Vector2u& viewSize)
{
	if (Unload())
	{
		switch (levelID)
		{
			case GameData::Level::Test:
			{
				CharacterObject* pHero = new ControllableCharacter();
				std::string svgPath = "../../support/levels/Level_Test.svg";
				m_pActiveLevel = new LevelData(m_Settings, pHero, svgPath);
				break;
			}

			default:
				assert(!"Invalid Level ID");
				break;
		}
	}

	return (m_pActiveLevel != nullptr);
}

bool DataManager::Unload()
{
	if (m_pActiveLevel != nullptr)
	{
		delete m_pActiveLevel;
		m_pActiveLevel = nullptr;
	}
	return (m_pActiveLevel == nullptr);
}

int DataManager::ProcessInput()
{
	int ret = 0;

	if (m_pActiveLevel != nullptr)
		ret += m_pActiveLevel->ProcessInput();

	for (auto& pMenu : m_lsMenuData)
	{
		if (pMenu->IsActive())
			ret += pMenu->ProcessInput();
	}
	return ret;
}

int DataManager::Update()
{
	int ret = 0;

	if (m_pActiveLevel != nullptr)
		ret += m_pActiveLevel->Update();
	
	for (unsigned int i = 0; i < m_lsMenuData.size(); ++i)
	{
		MenuData* pMenu = m_lsMenuData[i];
		if (pMenu != nullptr)
			ret += pMenu->Update();
	}
	
	return ret;
}

bool DataManager::ClearWindowEvents()
{
	m_WindowEvents.clear();
	return true;
}

bool DataManager::StoreWindowEvent(const sf::Event& windowEvent)
{
	m_WindowEvents[windowEvent.type].push_back(windowEvent);
	return true;
}

LevelData* DataManager::GetActiveLevel() const
{
	return m_pActiveLevel;
}

