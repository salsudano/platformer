#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "object_shape.h"
#include "object_style.h"

#include "component.h"
#include "state_component.h"
#include "physics_component.h"

#include "game_object.h"
#include "game_object_defs.h"

GameObject::GameObject()
	: m_bIsValid(false)
	, m_Description("game_object")
	, m_Position(0, 0)
	, m_Velocity(0, 0)
	, m_Friction(0.995f, 0.96f)
	, m_MinVelocity(00.01f, 00.01f)
	, m_MaxVelocity(5.00f, 10.00f)
	, m_Acceleration(0.10f, 25.00f)
	, m_LastXDirection(GameObject::Right)
{ }

GameObject::~GameObject()
{
}

void GameObject::SetDescription(const std::string& descr)
{
	m_Description = descr;
}

bool GameObject::IsValid() const
{
	return m_bIsValid;
}

const TPoint<float>& GameObject::GetPosition() const
{
	return m_Position;
}

const float& GameObject::GetXPosition() const
{
	return m_Position.x;
}

const float& GameObject::GetYPosition() const
{
	return m_Position.y;
}

void GameObject::SetXPosition(const float x)
{
	SetPosition(x, m_Position.y);
}

void GameObject::SetYPosition(const float y)
{
	SetPosition(m_Position.x, y);
}

void GameObject::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

GameObject::Direction GameObject::GetDirection() const
{
	if (m_Velocity.x == 0 && m_Velocity.y == 0)
		return Direction::Still;
	else if (m_Velocity.x > 0)
	{
		if (m_Velocity.y > 0)
			return Direction::LowerRight;
		else if (m_Velocity.y < 0)
			return Direction::UpperRight;
		return Direction::Right;
	}
	else if (m_Velocity.x < 0)
	{
		if (m_Velocity.y > 0)
			return Direction::LowerLeft;
		else if (m_Velocity.y < 0)
			return Direction::UpperLeft;
		return Direction::Left;
	}
	else if (m_Velocity.y > 0)
	{
		if (m_Velocity.x > 0)
			return Direction::LowerRight;
		else if (m_Velocity.x < 0)
			return Direction::LowerLeft;
		return Direction::Down;
	}
	else if (m_Velocity.y < 0)
	{
		if (m_Velocity.x > 0)
			return Direction::UpperRight;
		else if (m_Velocity.x < 0)
			return Direction::UpperLeft;
		return Direction::Up;
	}

	assert(false);
	return Direction::Still;
}

GameObject::Direction GameObject::GetYDirection() const
{
	return (m_Velocity.y > 0) ? Direction::Down
		 : (m_Velocity.y < 0) ? Direction::Up 
							  : Direction::Still;
}

GameObject::Direction GameObject::GetXDirection() const
{
	return m_LastXDirection = (m_Velocity.x > 0) ? Direction::Right
						    : (m_Velocity.x < 0) ? Direction::Left 
												 : m_LastXDirection;
}

bool GameObject::IsStill() const 
{ 
	return (m_Velocity.x == 0 && m_Velocity.y == 0);
}

bool GameObject::MovingRight() const 
{ 
	return ((GameObject::Right & this->GetDirection()) != 0);
}

bool GameObject::MovingLeft() const 
{ 
	return ((GameObject::Left & this->GetDirection()) != 0);
}

bool GameObject::MovingDown() const 
{ 
	return ((GameObject::Down & this->GetDirection()) != 0); 
}

bool GameObject::MovingUp() const 
{ 
	return ((GameObject::Up & this->GetDirection()) != 0);
}

const sf::Vector2<float>& GameObject::GetVelocity(Velocity type) const
{
	if  (type == Velocity::Current) return m_Velocity;
	else if (type == Velocity::Max) return m_MaxVelocity;
	else if (type == Velocity::Min) return m_MinVelocity;
	assert(false); return m_Velocity;
}

const float& GameObject::GetXVelocity(Velocity type) const
{
	return (type == Velocity::Current) ? m_Velocity.x
		 : (type == Velocity::Max)  ? m_MaxVelocity.x
		 : (type == Velocity::Min)  ? m_MinVelocity.x : m_Velocity.x;
}

const float& GameObject::GetYVelocity(Velocity type) const
{
	return (type == Velocity::Current) ? m_Velocity.y
		 : (type == Velocity::Max)  ? m_MaxVelocity.y
		 : (type == Velocity::Min)  ? m_MinVelocity.y : m_Velocity.y;
}

const sf::Vector2<float>& GameObject::GetFriction() const
{
	return m_Friction;
}

const float& GameObject::GetXFriction() const
{
	return m_Friction.x;
}

const float& GameObject::GetYFriction() const
{
	return m_Friction.y;
}

const sf::Vector2<float>& GameObject::GetAcceleration() const
{
	return m_Acceleration;
}

const float& GameObject::GetXAcceleration() const
{
	return m_Acceleration.x;
}

const float& GameObject::GetYAcceleration() const
{
	return m_Acceleration.y;
}

void GameObject::SetVelocity(const sf::Vector2<float>& vel)
{
	m_Velocity = vel;
}

void GameObject::SetXVelocity(const float xVel)
{
	m_Velocity.x = xVel;
}

void GameObject::SetYVelocity(const float yVel)
{
	m_Velocity.y = yVel;
}

