#ifndef __AI_CHARACTER_STATES_H
#define __AI_CHARACTER_STATES_H

#include "character_states.h"

// TODO: Figure out what to do with ProcessInput
class AICharacterStandingState : public CharacterStandingState
{
public:
				 AICharacterStandingState();
	virtual	    ~AICharacterStandingState();
		
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
	virtual	bool ProcessInput(CharacterObject* pGameObject)	{ return false; };
};

class AICharacterWalkingState : public CharacterWalkingState
{
public:
				 AICharacterWalkingState();
	virtual	    ~AICharacterWalkingState();

	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
	virtual	bool ProcessInput(CharacterObject* pGameObject)	{ return false; };
};

class AICharacterCrouchingState : public CharacterCrouchingState
{
public:
				AICharacterCrouchingState();
	virtual	   ~AICharacterCrouchingState();

	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
	virtual	bool ProcessInput(CharacterObject* pGameObject)	{ return false; };
};

class AICharacterJumpingState : public CharacterJumpingState
{
public:
				AICharacterJumpingState();
	virtual	   ~AICharacterJumpingState();

	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
	virtual	bool ProcessInput(CharacterObject* pGameObject)	{ return false; };
};

class AICharacterFallingState : public CharacterFallingState
{
public:
				AICharacterFallingState();
	virtual	   ~AICharacterFallingState();

	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData);
	virtual	bool ProcessInput(CharacterObject* pGameObject)	{ return false; };

};

#endif // __AI_CHARACTER_STATES_H