#ifndef __CONTROLLABLE_CHARACTER_STATES_H
#define __CONTROLLABLE_CHARACTER_STATES_H

#include "character_states.h"

class ControllableCharacterStandingState : public CharacterStandingState
{
public:
				 ControllableCharacterStandingState() { }
	virtual	    ~ControllableCharacterStandingState() { }
		
	virtual	bool ProcessInput(CharacterObject* pGameObject);
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
};

class ControllableCharacterWalkingState : public CharacterWalkingState
{
public:
				 ControllableCharacterWalkingState() { }
	virtual	    ~ControllableCharacterWalkingState() { }

	virtual	bool ProcessInput(CharacterObject* pGameObject);
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
};

class ControllableCharacterCrouchingState : public CharacterCrouchingState
{
public:
				ControllableCharacterCrouchingState() { }
	virtual	   ~ControllableCharacterCrouchingState() { }

	virtual	bool ProcessInput(CharacterObject* pGameObject);
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
};

class ControllableCharacterJumpingState : public CharacterJumpingState
{
public:
				ControllableCharacterJumpingState() { }
	virtual	   ~ControllableCharacterJumpingState() { }

	virtual	bool ProcessInput(CharacterObject* pGameObject);
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
};

class ControllableCharacterFallingState : public CharacterFallingState
{
public:
				ControllableCharacterFallingState() { }
	virtual	   ~ControllableCharacterFallingState() { }

	virtual	bool ProcessInput(CharacterObject* pGameObject);
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
};

#endif // __CONTROLLABLE_CHARACTER_STATES_H