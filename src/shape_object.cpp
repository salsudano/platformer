#include "shape_object.h"

ShapeObject::ShapeObject()
	: m_pShape(nullptr)
{ }

ShapeObject::ShapeObject(ObjectShape* pShape)
	: m_pShape(pShape)
{ }

ShapeObject::ShapeObject(const ShapeObject& rShapeObj)
	: m_pShape((rShapeObj.m_pShape != nullptr) ? new ObjectShape(*rShapeObj.m_pShape) : nullptr)
{ }

ShapeObject::~ShapeObject() 
{
	if (m_pShape != nullptr)
	{
		delete m_pShape;
		m_pShape = nullptr;
	}
}

int ShapeObject::Render(sf::RenderWindow& window)
{
	return m_pShape->RenderShape(window);
}

sf::RectangleShape ShapeObject::BoundingRectShape() const
{
	return m_pShape->BoundingRectShape();
}

TRect<float> ShapeObject::BoundingBox() const
{
	return m_pShape->BoundingBox();
}

const ObjectShape* ShapeObject::Shape() const 
{ 
	return m_pShape;
}
