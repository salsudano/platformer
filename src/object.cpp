#include "object.h"

Object::Object()
{
}

Object::~Object()
{
}

ObjectType Object::Type() const
{
	return m_Type;
}

const State* Object::CurrentState() const
{
	return m_CurrentStates.top();
}

template<typename T>
bool Object::AddComponent(T* pComponent)
{
	if (pComponent != nullptr)
	{
		Component::Type type = pComponent->Type();
		assert(m_ComponentMap[type] == nullptr);
		m_ComponentMap[type] = pComponent;
	}
	return false;
}