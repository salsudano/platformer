#include "component.h"

Component::Component(const Component::Type componentType)
	: m_Type(componentType)
{
}

Component::~Component()
{
}

const Component::Type Component::ComponentType() const 
{ 
	return m_Type; 
}
