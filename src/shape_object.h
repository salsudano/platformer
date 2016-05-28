#ifndef __SHAPE_OBJECT_H
#define __SHAPE_OBJECT_H

#include "game_object.h"
#include "object_shape.h"
#include "object_style.h"

class ShapeObject : public GameObject
{
public:
					ShapeObject();
	explicit		ShapeObject(ObjectShape* pShape);
	explicit		ShapeObject(const ShapeObject& rShapeObj);

	virtual		   ~ShapeObject();

	virtual int					Render(sf::RenderWindow& window);

	TRect<float>				BoundingBox()		const override final;
	sf::RectangleShape			BoundingRectShape() const;

	const ObjectShape*			Shape() const;

private:
	ObjectShape*				m_pShape;
};

#endif // __SHAPE_OBJECT_H