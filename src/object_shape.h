#ifndef __OBJECT_SHAPE_H
#define __OBJECT_SHAPE_H

#include <math.h>
#include "object_style.h"
#include "util\t_point.h"
#include "util\t_rect.h"
#include "SFML\Graphics.hpp"

enum class ShapeType
{
	Invalid,
	Line,
	Path,
	Rectangle,
	Circle,
	Ellipse,
	Polygon,
	PolyLine
};

class ObjectShape
{
public:
	ObjectShape() 
		: m_Type(ShapeType::Invalid)
	{
	}

	ObjectShape(ShapeType type) 
		: m_Type(type)
	{ 
	}

	ObjectShape(const ObjectShape* pShape)
		: m_Type(pShape != nullptr ? pShape->m_Type : ShapeType::Invalid)
		, m_BoundingBox(pShape != nullptr ? pShape->m_BoundingBox : TRect<float>())
	{ }

	virtual ~ObjectShape() 
	{ 
	}

	ShapeType Type() const 
	{ 
		return m_Type;
	}

	const sf::RectangleShape BoundingRectShape() const
	{
		return m_BoundingBox;
	}

	const TRect<float>& BoundingBox() const
	{
		return m_BoundingBox;
	} 

	virtual int RenderShape(sf::RenderWindow& window) 
	{ 
		return false; 
	}

protected:
	ShapeType		m_Type;
	TRect<float>	m_BoundingBox;
};


class Line
	: public ObjectShape
	, public sf::Shape
{
public:
	Line() 
		: ObjectShape(ShapeType::Line)
	{
		m_points.resize(getPointCount());
		update();
	}

	Line(const TPoint<float>& ptA, const TPoint<float>& ptB)
		: ObjectShape(ShapeType::Line)
	{
		m_points.resize(getPointCount());
		setPtA(ptA);
		setPtB(ptB);
		m_BoundingBox.PtA(ptA);
		m_BoundingBox.PtB(ptB);
	}

	virtual ~Line() 
	{ 
	}

	void setPtA(TPoint<float> pt)  
	{ 
		m_points[0] = pt;
		m_BoundingBox.PtA(pt);
		update();
	}

	void setPtB(TPoint<float> pt)  
	{	
		m_points[1] = pt; 
		m_BoundingBox.PtB(pt);
		update();
	}

	virtual sf::Vector2f getPoint(unsigned int index) const
    {
		return m_points[index];
	}

	virtual unsigned int getPointCount() const
    {
        return 2;
    }

	int RenderShape(sf::RenderWindow& window)
	{
		window.draw(reinterpret_cast<sf::Vertex*>(m_points.data()),	m_points.size(), sf::Lines);
		return 1;
	}

protected:
	std::vector<TPoint<float>> m_points;
};

/*
// A triangle can be represented as a circle with 3 points
class Triangle 
	: public ObjectShape
	, public sf::CircleShape
{
public:
	Triangle() 
		: ObjectShape(ShapeType::Circle) 
	{ 
		setPointCount(3);
	}

	virtual ~Triangle() 
	{
	}

	int RenderShape(sf::RenderWindow& window)
	{
		window.draw(*this);
		return 1;
	}
};
*/ 

class Rectangle
	: public ObjectShape
	, protected sf::RectangleShape
{
public:
	Rectangle() 
		: ObjectShape(ShapeType::Rectangle)
	{ 
	}

	virtual ~Rectangle() 
	{	
	}

	int RenderShape(sf::RenderWindow& window)
	{
		window.draw(*this);
		return 1;
	}
};


class PolyLine
	: public ObjectShape
	, public sf::Shape
{
public:
	PolyLine()
		: ObjectShape(ShapeType::PolyLine) 
	{ }

	virtual ~PolyLine()	
	{ 
	}

	void addPoint(const TPoint<float> pt)
	{
		m_points.push_back(pt);
		if (m_BoundingBox.IsEmpty())
			m_BoundingBox.PtA(pt);
		else
			m_BoundingBox.Include(pt);
	}

	virtual unsigned int getPointCount() const
    {
        return m_points.size();
    }

	virtual sf::Vector2f getPoint(unsigned int index) const
    {
		return m_points[index];
	}

	int RenderShape(sf::RenderWindow& window)
	{
		for (unsigned int i = 1; i < m_points.size(); ++i)
		{
			Line line(m_points[i - 1], m_points[i]);
			line.setFillColor(getFillColor());
			line.setOutlineColor(getOutlineColor());
			line.setOutlineThickness(getOutlineThickness());
			line.RenderShape(window);
		}
		return m_points.size();
	}

private:
	std::vector<TPoint<float>> m_points;
};

class Polygon 
	: public ObjectShape
	, public sf::ConvexShape
{
public:
	Polygon()
		: ObjectShape(ShapeType::Polygon) 
	{
		setPointCount(0);
	}
	
	virtual ~Polygon()	
	{ 
	}

	void addPoints(const std::vector<TPoint<float>>& points)
	{
		for (unsigned int i = 0; i < points.size(); ++i)
			addPoint(points[i]);
	}

	void addPoint(const TPoint<float> pt)
	{
		unsigned int ptCount = getPointCount();
		setPointCount(ptCount + 1);
		setPoint(ptCount, pt);

		if (m_BoundingBox.IsEmpty())
			m_BoundingBox.PtA(pt);
		else
			m_BoundingBox.Include(pt);
	}

	int RenderShape(sf::RenderWindow& window)
	{
		window.draw(*this);
		return 1;
	}
};

class Circle 
	: public ObjectShape
	, public sf::CircleShape
{
public:
	Circle() 
		: ObjectShape(ShapeType::Circle) 
	{ 
	}

	virtual ~Circle() 
	{
	}

	int RenderShape(sf::RenderWindow& window)
	{
		window.draw(*this);
		return 1;
	}
};

class Ellipse 
	: public ObjectShape
	, public sf::Shape
{
public :
    explicit Ellipse(const TPoint<float>& radius = TPoint<float>(0, 0)) 
		: m_radius(radius)
		, m_pointCount(30)
    {
        update();
    }

    void setRadius(const TPoint<float>& radius)
    {
        m_radius = radius;
        update();
    }

    const TPoint<float>& getRadius() const
    {
        return m_radius;
    }
	
	virtual unsigned int getPointCount() const
    {
        return m_pointCount;
    }

	virtual sf::Vector2f getPoint(unsigned int index) const
    {
		const float pi = 3.14159265358979323846f;
        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;
        return TPoint<float>(m_radius.x + x, m_radius.y + y);
    }

	virtual int RenderShape(sf::RenderWindow& window)
	{
		window.draw(*this);
		return 1;
	}

private:
    TPoint<float> m_radius;
//	TPoint<float> m_center; // TODO: Fix this class and fill in m_BoundingBox
	unsigned int m_pointCount;
};

#endif // __OBJECT_SHAPE_H