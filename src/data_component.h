#ifndef __DATA_COMPONENT_H
#define __DATA_COMPONENT_H

#include "SFML\Graphics\RenderWindow.hpp"

class DataComponent
{
public:
	DataComponent() 
		: m_bInitialized(false) 
		, m_bActive(false)
	{ }
	virtual	~DataComponent() { }

	virtual int	 ProcessInput()	= 0;
	virtual int	 Update()		= 0;

	bool IsActive() const { return m_bActive; }

protected:
	bool m_bInitialized;
	bool m_bActive;
};

#endif // __DATA_COMPONENT_H
