#ifndef __INTERACTIVE_OBJECT_H
#define __INTERACTIVE_OBJECT_H

#include "game_object.h"

class LevelData;

// Defines objects that are able to interact with character objects (platforms, fire, water, bullets, etc...)
class InteractiveObject : public GameObject
{
public:
			 InteractiveObject();
	virtual ~InteractiveObject();

	virtual bool Update(const LevelData* pLevelData);
};

// Defines all inactive foreground game objects
class CementBlockObject : public InteractiveObject
{
public:
			 CementBlockObject();
			 CementBlockObject(const float x);
	virtual ~CementBlockObject();
};


#endif // __INTERACTIVE_OBJECT_H