#include "character_ai_states.h"

#include "component.h"
#include "character_object.h"

AICharacterStandingState::AICharacterStandingState()
{
}

AICharacterStandingState::~AICharacterStandingState()
{
}

bool AICharacterStandingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

AICharacterWalkingState::AICharacterWalkingState()
{
}

AICharacterWalkingState::~AICharacterWalkingState()
{
}

bool AICharacterWalkingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

AICharacterCrouchingState::AICharacterCrouchingState()
{
}

AICharacterCrouchingState::~AICharacterCrouchingState()
{
}

bool AICharacterCrouchingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

AICharacterJumpingState::AICharacterJumpingState()
{
}

AICharacterJumpingState::~AICharacterJumpingState()
{
}

bool AICharacterJumpingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

AICharacterFallingState::AICharacterFallingState()
{
}

AICharacterFallingState::~AICharacterFallingState()
{
}

bool AICharacterFallingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	return true;
}