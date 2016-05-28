#include "interactive_states.h"
#include "game_object.h"
#include "level_data.h"

InteractiveObjectState::InteractiveObjectState()	
{
}

InteractiveObjectState::InteractiveObjectState(const std::string& texturePath)	
{
}

InteractiveObjectState::~InteractiveObjectState()
{
}

bool InteractiveObjectState::Update(GameObject* pGameObject, const LevelData* pLevelData)
{
	return false;
}

StillInteractiveState::StillInteractiveState() 
{
}

StillInteractiveState::StillInteractiveState(const std::string& texturePath)
{
}

StillInteractiveState::~StillInteractiveState() 
{
}

bool StillInteractiveState::Update(GameObject* pGameObject, const LevelData* pLevelData)
{
	return false;
}

MovableInteractiveState::MovableInteractiveState()
{
}

MovableInteractiveState::MovableInteractiveState(const std::string& texturePath)
	: InteractiveObjectState(texturePath)
{
}
	
MovableInteractiveState::~MovableInteractiveState() 
{ 
}

bool MovableInteractiveState::Update(GameObject* pGameObject, const LevelData* pLevelData)
{
	return false;
}
