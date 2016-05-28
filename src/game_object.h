#ifndef __GAME_OBJECT_H
#define __GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "object_shape.h"
#include "object_style.h"

#include "state_component.h"
#include "game_object_defs.h"
#include "component.h"

class LevelData;

class GameObject 
{
public:
	enum Direction
	{
		Still = (0),
		Up    = (1 << 0),
		Down  = (1 << 1),
		Left  = (1 << 2),
		Right = (1 << 3),
		UpperRight = (Up | Right),
		UpperLeft  = (Up | Left),
		LowerRight = (Down | Right),
		LowerLeft  = (Down | Left)
	};

	enum class Velocity { Current, Max, Min	};

public:
									GameObject();
	virtual						   ~GameObject();

	virtual int						Render(sf::RenderWindow& window) = 0;
	virtual TRect<float>			BoundingBox()		const = 0;

	bool							IsValid()			const;
	bool							IsStill()			const;
	bool							MovingRight()		const;
	bool							MovingLeft()		const;
	bool							MovingDown()		const;
	bool							MovingUp()			const;

	void							SetDescription(const std::string& type);

	const TPoint<float>&			GetPosition()		const;
	const float&					GetXPosition()		const;
	const float&					GetYPosition()		const;

	virtual void					SetPosition(const float x, const float y);
	void							SetXPosition(const float x);
	void							SetYPosition(const float y);

	Direction						GetDirection()		const;
	Direction						GetXDirection()		const;
	Direction						GetYDirection()		const;

	const sf::Vector2<float>&		GetVelocity(Velocity type = Velocity::Current)  const;
	const float&					GetXVelocity(Velocity type = Velocity::Current) const;
	const float&					GetYVelocity(Velocity type = Velocity::Current) const;

	const sf::Vector2<float>&		GetFriction()		const;
	const float&					GetXFriction()		const;
	const float&					GetYFriction()		const;

	const sf::Vector2<float>&		GetAcceleration()	const;
	const float&					GetXAcceleration()	const;
	const float&					GetYAcceleration()	const;

	void							SetVelocity(const sf::Vector2<float>& vel);
	void							SetXVelocity(const float xVel);
	void							SetYVelocity(const float yVel);


protected:
	bool							m_bIsValid;
	std::string						m_Description;
	TPoint<float>					m_Position;
	sf::Vector2<float>				m_Velocity;
	sf::Vector2<float>				m_Friction;
	sf::Vector2<float>				m_MinVelocity;
	sf::Vector2<float>				m_MaxVelocity;
	sf::Vector2<float>				m_Acceleration;
	mutable Direction				m_LastXDirection;
};

#include "util\utils.h"
DECLARE_BITWISE_OPERATORS( GameObject::Direction );

#endif // __GAME_OBJECT_H