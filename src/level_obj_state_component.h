#ifndef __LEVEL_OBJ_STATE_COMPONENT_H
#define __LEVEL_OBJ_STATE_COMPONENT_H

/*
#include "state_component.h"
class LevelObjectStateComponent : public StateComponent
{
public:
	LevelObjectStateComponent()
	{
	}

	virtual	~LevelObjectStateComponent() 
	{
	}

	ObjectState* CurrentState() const
	{
		if (m_StateStack.size() > 0)
			return m_StateStack.back();
		return nullptr;
	}

	const sf::Sprite* CurrentSprite() const
	{
		ObjectState* pCurrState = this->CurrentState();
		if (pCurrState != nullptr)
			return &pCurrState->GetSprite();
		return nullptr;
	}

protected:
	std::map<std::string, ObjectState*> m_StateTable;	 // table that contains all possible states for the object
	std::vector<ObjectState*>			m_StateStack;	 // object's state's (whatever is on top of the stack is the current state)
	std::string							m_TexturePath;   // where to find the textures for each state this component will manage
	bool								m_bInitialized;  // has the state stack/table been initialized?
};
*/
#endif //__LEVEL_OBJ_STATE_COMPONENT_H