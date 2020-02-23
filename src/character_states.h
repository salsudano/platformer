#ifndef __CHARACTER_OBJ_STATES_H
#define __CHARACTER_OBJ_STATES_H

#include "object_state.h"
#include "character_actions.h"

class LevelData;
class CharacterObject;

class CharacterState : public ObjectState<CharacterAction>
{
public:
				 CharacterState() { }
	virtual		~CharacterState() { }

	virtual	bool ProcessInput(CharacterObject* pGameObject)					 = 0;
	virtual bool Update(CharacterObject* pGameObject, LevelData* pLevelData) = 0;
};

class CharacterStandingState : public CharacterState
{
public:
	CharacterStandingState() 
	{ 
		this->Action(CharacterAction::Stand); 
		this->AddTexture("../../support/textures/object/character/cat/standing.png");
	}
	
	virtual	~CharacterStandingState() 
	{ 
	}
		
	virtual	bool ProcessInput(CharacterObject* pGameObject)					 = 0;
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData) = 0;
};

class CharacterWalkingState : public CharacterState
{
public:
	CharacterWalkingState() 
	{ 
		this->Action(CharacterAction::Walk); 
		this->AddTexture("../../support/textures/object/character/hero/running/running_1.png");
		this->AddTexture("../../support/textures/object/character/hero/running/running_2.png");
		this->AddTexture("../../support/textures/object/character/hero/running/running_3.png");
		this->AddTexture("../../support/textures/object/character/hero/running/running_4.png");
		this->AddTexture("../../support/textures/object/character/hero/running/running_5.png");
		this->AddTexture("../../support/textures/object/character/hero/running/running_6.png");
	}
	
	virtual	~CharacterWalkingState() 
	{ 
	}

	virtual	bool ProcessInput(CharacterObject* pGameObject)					 = 0;
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData) = 0;

protected:
	TPoint<float>	 m_LastPos;
	static const int MOVE_THRESHOLD = 25;
};

class CharacterCrouchingState : public CharacterState
{
public:
	CharacterCrouchingState() 
	{ 
		this->Action(CharacterAction::Crouch); 
		this->AddTexture("../../support/textures/object/character/cat/Crouching.png");
	}
	
	virtual	~CharacterCrouchingState() 
	{ 
	}

	virtual	bool ProcessInput(CharacterObject* pGameObject)					 = 0;
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData) = 0;
};

class CharacterJumpingState : public CharacterState
{
public:
	CharacterJumpingState() 
		: m_bFirstUpdate(true)
	{ 
		this->Action(CharacterAction::Jump); 
		this->AddTexture("../../support/textures/object/character/cat/jumping.png");
	}

	virtual	~CharacterJumpingState() 
	{ 
	}

	virtual bool PreActivate() 
	{
		m_accelCount = 0;
		m_bFirstUpdate = true; 
		m_OrigPosition.reset();
		return true;
	}

	virtual	bool ProcessInput(CharacterObject* pGameObject)					 = 0;
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData) = 0;

protected:
	bool		  m_bFirstUpdate;
	int			  m_accelCount;
	TPoint<float> m_OrigPosition;
};

class CharacterFallingState : public CharacterState
{
public:
	CharacterFallingState() 
	{ 
		this->Action(CharacterAction::Fall); 
		this->AddTexture("../../support/textures/object/character/cat/falling.png");
	}
	
	virtual	~CharacterFallingState() 
	{ 
	}

	virtual	bool ProcessInput(CharacterObject* pGameObject)					 = 0;
	virtual	bool Update(CharacterObject* pGameObject, LevelData* pLevelData) = 0;

protected:
	bool		  m_bFirstUpdate;
	TPoint<float> m_OrigPosition;
};

#endif // __CHARACTER_OBJ_STATES_H