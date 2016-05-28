#ifndef __PHYSICS_COMPONENT_H
#define __PHYSICS_COMPONENT_H

#include "component.h"
#include "game_object_defs.h"

class LevelData;
class LevelObject;
class CharacterObject;
template<typename T> class TRect;
template<typename T> class RTree;

class PhysicsComponent : public Component
{
public:
					PhysicsComponent();
	virtual		   ~PhysicsComponent();

	virtual	int		Update(CharacterObject* pGameObject, LevelData* pLevelData) const;

private:
	bool	ApplyLevelPhysics(CharacterObject* pGameObject, const LevelData* pLevelData) const;
	bool	ClampVelocity(CharacterObject* pGameObject) const;
	bool	UpdatePosition(CharacterObject* pGameObject) const;
	bool	ResolveCollisions(CharacterObject* pCharacterObj, const RTree<LevelObject>& objectBoundsTree) const;
};

#endif // __PHYSICS_COMPONENT_H