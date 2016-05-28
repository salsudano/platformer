#ifndef __INACTIVE_OBJ_STATES_H
#define __INACTIVE_OBJ_STATES_H

#include "object_state.h"

class LevelData;
class GameObject;
enum class ObjectAction;

// State for objects that are static (and don't move)
class InactiveObjectState : public ObjectState<ObjectAction>
{
public:
				 InactiveObjectState();
	virtual	    ~InactiveObjectState();

	virtual	bool ProcessInput(GameObject* pGameObject)						  = 0;
	virtual	bool Update(GameObject* pGameObject, const LevelData* pLevelData) = 0;
};

class StillInactiveState : public InactiveObjectState
{
public:
				 StillInactiveState();
	virtual	    ~StillInactiveState();

	virtual	bool ProcessInput(GameObject* pGameObject);
	virtual	bool Update(GameObject* pGameObject, const LevelData* pLevelData);
};

class BackgroundState : public StillInactiveState
{
public:
				 BackgroundState();
	virtual	    ~BackgroundState();

	virtual	bool ProcessInput(GameObject* pGameObject);
	virtual	bool Update(GameObject* pGameObject, const LevelData* pLevelData);
};


class MovableInactiveState : public InactiveObjectState
{
public:
				 MovableInactiveState();
	virtual	    ~MovableInactiveState();

	virtual	bool ProcessInput(GameObject* pGameObject);
	virtual	bool Update(GameObject* pGameObject, const LevelData* pLevelData);
};

#endif // __INACTIVE_OBJ_STATES_H