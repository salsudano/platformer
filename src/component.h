#ifndef __COMPONENT_H
#define __COMPONENT_H

class LevelData;
class GameObject;

class Component
{
public:
	enum class Type
	{
		Shape,
		Style,
		State,
		Physics,
		Graphics,
		Input
	};

public:
				Component(const Component::Type type);
	virtual	   ~Component();

	const Type	ComponentType() const;

protected:
	const Type	m_Type;
};

#endif //__COMPONENT_H