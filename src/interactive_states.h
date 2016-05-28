#ifndef __INTERACTIVE_OBJ_STATES_H
#define __INTERACTIVE_OBJ_STATES_H

#include <string>
#include "object_state.h"

class LevelData;
class GameObject;
enum class ObjectAction;

// State for objects that are dynamic (and can move or change in any way)
class InteractiveObjectState : public ObjectState<ObjectAction>
{
public:
				 InteractiveObjectState();
				 InteractiveObjectState(const std::string& texturePath);
	virtual		~InteractiveObjectState();

	virtual bool Update(GameObject* pGameObject, const LevelData* pLevelData);
};


class StillInteractiveState : public InteractiveObjectState
{
public:
				 StillInteractiveState();
				 StillInteractiveState(const std::string& texturePath);
	virtual		~StillInteractiveState();

	bool		 Update(GameObject* pGameObject, const LevelData* pLevelData);
};


class MovableInteractiveState : public InteractiveObjectState
{
public:
				 MovableInteractiveState();
				 MovableInteractiveState(const std::string& texturePath);
	virtual		~MovableInteractiveState();

	bool		 Update(GameObject* pGameObject, const LevelData* pLevelData);
};


#endif // __INTERACTIVE_OBJ_STATES_H