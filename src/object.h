#ifndef __OBJECT_H
#define __OBJECT_H

#include <map>
#include <stack>

#include <SFML\Graphics.hpp>

class Command;
class Component;
class StateManager;

enum class ComponentType;

enum class ObjectType
{
	Text,
	Background,
	ForeGround,
	Character,
	Structural
};

enum class ObjectDirection
{
	None,
	Up,
	Down,
	Left,
	Right
};

class Object
{
public:
				Object();
	virtual	   ~Object();

	ObjectType		Type()			const;
	const State*	CurrentState()	const;


	template<typename T> 
	bool AddComponent(T* pComponent);

protected:
	bool										m_IsValid;			// Is the object valid?
	ObjectType									m_Type;				// Object's type
	std::string									m_Name;				// Object's name
	sf::Vector2<float>							m_Position;			// Object's position
	sf::Vector2<ObjectDirection>				m_LastDir;			// Last direction of movement (x and y axis)
	std::map<ComponentType, Component*>			m_ComponentMap;		// A collection of the Object's behavior defining components
	
	StateManager								m_StateMgr;			// Manages all data associated with the object's state

	// Debug?
	std::string									m_TexturePath;		// Path to object's texture
};

class MoveableObject : public Object
{
public:
				MoveableObject() { }
	virtual	   ~MoveableObject() { }

protected:
	sf::Vector2<float>	m_Velocity;
};


#endif // __OBJECT_H