#ifndef __LEVEL_OBJECT_H
#define __LEVEL_OBJECT_H

#include "shape_object.h"

class LevelObject : public ShapeObject
{
public:
					LevelObject();
					LevelObject(ObjectShape* pShape);
	virtual		   ~LevelObject();

	virtual int		ProcessInput(); 
	virtual int		Update(LevelData* pLevelData);
	virtual int		Render(sf::RenderWindow& window);

protected:
	// TODO: Add level object components...

};

#endif // __LEVEL_OBJECT_H