#ifndef __CHARACTER_STATE_COMPONENT_H
#define __CHARACTER_STATE_COMPONENT_H

#include "input_component.h"
#include "character_controllable_states.h"

class CharacterStateComponent : public StateComponent<CharacterState, CharacterAction>
{
public:
	CharacterStateComponent()
	{
		this->AddNewState(new ControllableCharacterStandingState());
		this->AddNewState(new ControllableCharacterCrouchingState());
		this->AddNewState(new ControllableCharacterWalkingState());
		this->AddNewState(new ControllableCharacterJumpingState());
		this->AddNewState(new ControllableCharacterFallingState());
	}
};

#endif //__CHARACTER_STATE_COMPONENT_H