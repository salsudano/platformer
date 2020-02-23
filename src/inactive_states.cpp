#include "inactive_states.h"
#include "level_data.h"

InactiveObjectState::InactiveObjectState() 
{ 
	AddTexture("../../support/game/textures/object/inactive/background/mountains.png");
}

InactiveObjectState::~InactiveObjectState() 
{
}

StillInactiveState::StillInactiveState() 
{
}

StillInactiveState::~StillInactiveState() 
{
}

bool StillInactiveState::ProcessInput(GameObject* pGameObject)						   
{ 
	return false; 
}

bool StillInactiveState::Update(GameObject* pGameObject, const LevelData* pLevelData) 
{ 
	return false; 
}

BackgroundState::BackgroundState() 
{
	AddTexture("../../support/game/textures/object/inactive/background/mountains.png");
}
BackgroundState::~BackgroundState() { }

bool BackgroundState::ProcessInput(GameObject* pGameObject)
{
	return false; 
}

bool BackgroundState::Update(GameObject* pGameObject, const LevelData* pLevelData) 
{ 
	return false; 
}

MovableInactiveState::MovableInactiveState() 
{ 
}

MovableInactiveState::~MovableInactiveState() 
{ 
}

bool MovableInactiveState::ProcessInput(GameObject* pGameObject)						   
{ 
	return false; 
}

bool MovableInactiveState::Update(GameObject* pGameObject, const LevelData* pLevelData) 
{ 
	return false; 
}
