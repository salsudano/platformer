#ifndef __INPUT_COMPONENT_H
#define __INPUT_COMPONENT_H

#include <unordered_map>

#include <SFML\Window.hpp>

#include "component.h"
#include "character_actions.h"

enum class InputType
{
	MouseAndKeyboard,
	Controller,
};

class ActionInput
{
public:
				ActionInput() { }
	virtual    ~ActionInput() { }

	bool HasKeyboardInputs()	const { return KeyboardInputs.size()   > 0; }
	bool HasMouseInputs()		const { return MouseInputs.size()	   > 0; }
	bool HasControllerInputs()	const { return ControllerInputs.size() > 0; }

	std::vector<sf::Keyboard::Key>	KeyboardInputs;
	std::vector<sf::Mouse::Button> 	MouseInputs;
	std::vector<sf::Joystick::Axis> ControllerInputs;
};

template <typename TAction>
class InputComponent : public Component
{
public:
	InputComponent() 
		: Component(Component::Type::Input)
		, m_ActiveInput(InputType::MouseAndKeyboard)
	{ }
	
	virtual	~InputComponent() 
	{ 
	}

	void ActiveInput(InputType input)
	{
		m_ActiveInput = input;
	}

	InputType ActiveInput() const
	{
		return m_ActiveInput;
	}

	bool AddKeyForAction(TAction action, sf::Keyboard::Key key)
	{
		ActionInput& input = m_ActionInputMap[action];
		input.KeyboardInputs.push_back(key);
		return true;
	}

	bool AddKeyForAction(TAction action, sf::Mouse::Button mouse)
	{
		ActionInput& input = m_ActionInputMap[action];
		input.MouseInputs.push_back(mouse);
		return true;
	}

	bool AddKeyForAction(TAction action, sf::Joystick::Axis joystick)
	{
		ActionInput& input = m_ActionInputMap[action];
		input.JoystickInput.push_back(joystick);
		return true;
	}

	bool InputDetectedForAction(TAction action)
	{
		bool inputDetected = false;

		const ActionInput& input = m_ActionInputMap[action];
		if (input.HasKeyboardInputs())
		{
			for (unsigned int i = 0; i < input.KeyboardInputs.size() && !inputDetected; ++i)
			{
				const auto& key = input.KeyboardInputs[i];
				inputDetected = sf::Keyboard::isKeyPressed(key);
				m_ActiveInput = InputType::MouseAndKeyboard;
			}
		}
		
		if (!inputDetected && input.HasMouseInputs())
		{
			for (unsigned int i = 0; i < input.MouseInputs.size() && !inputDetected; ++i)
			{
				const auto& mouseInput = input.MouseInputs[i];
				inputDetected = sf::Mouse::isButtonPressed(mouseInput);
				m_ActiveInput = InputType::MouseAndKeyboard;
			}
		}

		if (!inputDetected && input.HasControllerInputs())
		{
			for (unsigned int i = 0; i < input.ControllerInputs.size() && !inputDetected; ++i)
			{
				const auto& mouseInput = input.MouseInputs[i];
				inputDetected = sf::Mouse::isButtonPressed(mouseInput);
				m_ActiveInput = InputType::Controller;
			}
		}

		return inputDetected;
	}

private:
	InputType									m_ActiveInput;
	std::unordered_map<TAction, ActionInput>	m_ActionInputMap;
};

#endif //__INPUT_COMPONENT_H