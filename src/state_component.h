#ifndef __STATE_COMPONENT_H
#define __STATE_COMPONENT_H

#include <assert.h>
#include <iostream>

#include "component.h"

#include "character_states.h"
#include "inactive_states.h"
#include "interactive_states.h"
#include "game_object.h"

template<typename TState, typename TAction> 
class StateComponent : public Component
{
public:
	StateComponent()
		: Component(Component::Type::State)
		, m_pPreviousState(nullptr)
		, m_bInitialized(false)
		, m_bStateChanged(false)
	{ }

	virtual	~StateComponent() 
	{
		for (auto& i : m_StateTable)
		{
			TState* pState = i.second;
			assert(pState != nullptr);
			if (pState != nullptr)
				delete pState;
			pState = nullptr;
		}
	}

	template<typename TObject>
	int	Update(TObject* pObject, LevelData* pLevelData)
	{
		TState* pState = this->CurrentState();
		if (pState != nullptr)
		{
			if (m_bStateChanged && (m_pPreviousState != nullptr))
			{
				sf::Sprite& prevSprite = m_pPreviousState->GetSprite();
				sf::Sprite& newSprite = pState->GetSprite();
				const int prevHeight = prevSprite.getTextureRect().height;
				const int newHeight = newSprite.getTextureRect().height;
				TPoint<float> pos = pObject->GetPosition();
				
				if (newHeight > prevHeight)
					pos.MoveUp(static_cast<float>(newHeight - prevHeight));
				else if (newHeight < prevHeight)
					pos.MoveDown(static_cast<float>(prevHeight - newHeight));
				pObject->SetPosition(pos);
			}

			m_bStateChanged = false;
			return pState->Update(pObject, pLevelData);
		}
		return 0;
	}

	bool AddNewState(TState* pState)
	{
		m_StateTable[pState->Action()] = pState;
		if (m_StateStack.size() == 0)
			m_bInitialized = PushState(pState->Action());
		return true;
	}

	bool PushState(const TAction& action)
	{
		TState* pState = m_StateTable[action];
		assert(pState != nullptr);

		m_bStateChanged  = true;
		m_pPreviousState = this->CurrentState();

		pState->Activate();
		m_StateStack.push_back(pState);
		return true;
	}

	bool PopState()
	{
		assert(m_StateStack.size() > 1);
		if (m_StateStack.size() > 1)
		{
			m_bStateChanged  = true;
			m_pPreviousState = this->CurrentState();

			m_StateStack[m_StateStack.size() - 1]->Deactivate();
			m_StateStack.pop_back();
			return true;
		}
		return false;
	}

	bool SwapCurrentState(const TAction action)
	{
		assert(m_StateStack.size() > 1);
		if (m_StateStack.size() > 1)
			return (PopState() && PushState(action));
		return false;
	}
	
	TState* CurrentState() const
	{
		if (m_StateStack.size() > 0)
			return m_StateStack.back();
		return nullptr;
	}

	sf::Sprite* CurrentSprite()
	{
		TState* pCurrState = this->CurrentState();
		if (pCurrState != nullptr)
			return &pCurrState->GetSprite();
		return nullptr;
	}

protected:
	std::map<TAction, TState*>	 m_StateTable;      // table that contains all possible states for the object
	std::vector<TState*>		 m_StateStack;      // object's state's (whatever is on top of the stack is the current state)
	std::string					 m_TexturePath;     // where to find the textures for each state this component will manage
	TState*						 m_pPreviousState;  // records the object's previous state
	bool						 m_bInitialized;    // has the state stack/table been initialized?
	bool						 m_bStateChanged;   // has the state changed since the last update?
};

#endif //__STATE_COMPONENT_H