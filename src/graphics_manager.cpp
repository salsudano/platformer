#include <assert.h>

#include "graphics_manager.h"
#include "data_manager.h"
#include "character_object.h"
#include "inactive_object.h"
#include "level_data.h"

GraphicsManager::GraphicsManager(sf::RenderWindow& rMainWindow)
	: m_rWindow(rMainWindow)
	, m_bDrawDebugInfo(true)
{
}

GraphicsManager::~GraphicsManager()
{
}

bool GraphicsManager::RenderScene(const DataManager* pDataMgr)
{
	m_rWindow.clear(sf::Color::Cyan);
	
	LevelData* pActiveLevel = pDataMgr->GetActiveLevel();
	if (pActiveLevel != nullptr)
		pActiveLevel->Render(m_rWindow);
	
	m_rWindow.display();
	
	return true;
}
