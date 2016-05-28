#include "character_input_component.h"

CharacterInputComponent::CharacterInputComponent()
{
	this->AddKeyForAction(CharacterAction::MoveLeft,	sf::Keyboard::Left);
	this->AddKeyForAction(CharacterAction::MoveRight,	sf::Keyboard::Right);
	this->AddKeyForAction(CharacterAction::Crouch,		sf::Keyboard::Down);
	this->AddKeyForAction(CharacterAction::Run,			sf::Keyboard::LControl);
	this->AddKeyForAction(CharacterAction::Run,			sf::Keyboard::RControl);
	this->AddKeyForAction(CharacterAction::Jump,		sf::Keyboard::Space);
	this->AddKeyForAction(CharacterAction::Jump,		sf::Keyboard::Up);
}

