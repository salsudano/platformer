#ifndef __CHARACTER_INPUT_COMPONENT_H
#define __CHARACTER_INPUT_COMPONENT_H

#include "input_component.h"

enum class CharacterAction;

class CharacterInputComponent : public InputComponent<CharacterAction>
{
public:
	CharacterInputComponent();
};

#endif // __CHARACTER_INPUT_COMPONENT_H
