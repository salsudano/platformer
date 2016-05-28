#ifndef __STATE_MANAGER_H
#define __STATE_MANAGER_H

#include <map>
#include <stack>

class State;

class StateManager
{
private:
	std::stack<State*>				m_CurrentStates;	   // Stack containing all of the Object's current states
	std::map<StateType, State*>		m_StateMap;	   // table that contains all possible states for the object
};

#endif //__STATE_MANAGER_H