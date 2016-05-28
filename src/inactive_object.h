#ifndef __INACTIVE_OBJECT_H
#define __INACTIVE_OBJECT_H

#include "level_object.h"
#include "util\svg_element.h"

// Defines background or foreground objects that aren't able to interact with character objects in any way (art only)
class InactiveLevelObject : public LevelObject
{
public:
	InactiveLevelObject() 
	{
		SetDescription("inactive");
	}

	InactiveLevelObject(ObjectShape* pShape)
		: LevelObject(pShape)
	{ 
		SetDescription("inactive");
	}

	virtual ~InactiveLevelObject() 
	{
	}
};

// Defines background or foreground objects that aren't able to interact with character objects in any way (art only)
class BackgroundLevelObject : public InactiveLevelObject
{
public:
				BackgroundLevelObject();
				BackgroundLevelObject(ObjectShape* pShape);

	virtual	   ~BackgroundLevelObject();

	int			Update(LevelData* pLevelData);

private:
	TPoint<float>	m_OrigLocation;
};


#endif // __INACTIVE_OBJECT_H