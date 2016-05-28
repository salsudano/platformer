#ifndef __SVG_ELEMENT_H
#define __SVG_ELEMENT_H

#include <string>
#include <sstream>
#include <assert.h>

#include "SFML\Graphics.hpp"

#include "util\svg_defs.h"
#include "util\xml_node.h"
#include "util\t_point.h"

#include "object_shape.h"
#include "object_style.h"

class SVGElement
{
public:
	SVGElement()
		: m_bIsValid(false)
	{ 
	}

	SVGElement(const XMLNode& node)
		: m_bIsValid(true)
	{

		for (unsigned int i = 0; i < node.AttributeCount(); ++i)
		{
			const XMLAttribute* pAttr = node.GetAttribute(i);
			if (pAttr != nullptr)
			{
				if (pAttr->Description() == SVG::Element::AttrID::Fill)
					m_StyleInfo.FillColor(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::StrokeColor)
					m_StyleInfo.OutlineColor(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::StrokeWidth)
					m_StyleInfo.OutlineThickness(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::StrokeMiterLimit)
					m_StyleInfo.OutlineMiterLimit(pAttr->Value());
			}
		}

		if ((m_StyleInfo.OutlineThickness() == 0) && 
			(m_StyleInfo.OutlineColor() != sf::Color(0, 0, 0, 255)))
		{
			// The SVG format implies that the width is 1 
			// if a color is defined, but a thickness isn't.
			m_StyleInfo.OutlineThickness(1.0f);
		}
	}

	virtual ~SVGElement() 
	{ 
	}

	const bool IsValid() const
	{
		return m_bIsValid;
	}

	virtual	ObjectShape* CloneShape() const = 0;

protected:
	template<typename T>
	T TStringConvert(const std::string& str)
	{
		T ret;
		std::stringstream ss(str);
		ss >> ret;
		return ret;
	}

protected:
	bool		m_bIsValid;
	ObjectStyle m_StyleInfo;
};

class SVGLine 
	: public SVGElement
	, public Line
{
public:
	SVGLine(const XMLNode& node)
		: Line()
		, SVGElement(node)
	{
		TPoint<float> ptA, ptB;
		for (unsigned int i = 0; i < node.AttributeCount(); ++i)
		{
			const XMLAttribute* pAttr = node.GetAttribute(i);
			if (pAttr != nullptr)
			{
				if (pAttr->Description() == SVG::Element::AttrID::X1)
					ptA.x = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::X2)
					ptB.x = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::Y1)
					ptA.y = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::Y2)
					ptB.y = TStringConvert<float>(pAttr->Value());
			}
		}

		if (ptA == ptB)
			m_bIsValid = false;
		else
		{
			this->setPtA(ptA);
			this->setPtA(ptB);
			this->setFillColor(m_StyleInfo.FillColor());
			this->setOutlineColor(m_StyleInfo.OutlineColor());
			this->setOutlineThickness(m_StyleInfo.OutlineThickness());
		}
	}
	
	virtual ~SVGLine() 
	{ 
	}

	ObjectShape* CloneShape() const
	{
		return new Line(*this);
	}
};


class SVGRectangle 
	: public SVGElement
	, public Rectangle
{
public:
	SVGRectangle(const XMLNode& node)
		: Rectangle()
		, SVGElement(node)
	{
		TPoint<float> size(0.0f, 0.0f);
		TPoint<float> position(0.0f, 0.0f);
		for (unsigned int i = 0; i < node.AttributeCount(); ++i)
		{
			const XMLAttribute* pAttr = node.GetAttribute(i);
			if (pAttr != nullptr)
			{
				if (pAttr->Description() == SVG::Element::AttrID::X)
					position.x = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::Y)
					position.y = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::Height)
					size.y = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::Width)
					size.x = TStringConvert<float>(pAttr->Value());
			}
		}

		if (size.x == 0 && size.y == 0)
			m_bIsValid = false;
		else
		{
			this->setPosition(position);
			this->setSize(size);
			this->setFillColor(m_StyleInfo.FillColor());
			this->setOutlineColor(m_StyleInfo.OutlineColor());
			this->setOutlineThickness(m_StyleInfo.OutlineThickness());

			this->m_BoundingBox.PtA(position);
			this->m_BoundingBox.PtB(position + size);
		}
	}
	
	SVGRectangle(std::string x, std::string y, std::string height, std::string width) 
	{
		TPoint<float> size(0.0f, 0.0f);
		TPoint<float> position(0.0f, 0.0f);
		if (x.length() > 0)
		{
			std::stringstream ssX(x); 
			ssX >> position.x;
		}
		if (y.length() > 0)
		{
			std::stringstream ssY(y); 
			ssY >> position.y;
		}
		if (height.length() > 0)
		{
			std::stringstream ssLength(height); 
			ssLength >> size.y;
		}
		if (width.length() > 0)
		{
			std::stringstream ssWidth(width); 
			ssWidth >> size.x;
		}

		if (size.x == 0 && size.y == 0)
			m_bIsValid = false;
		else
		{
			this->setPosition(position);
			this->setSize(size);
			this->setFillColor(m_StyleInfo.FillColor());
			this->setOutlineColor(m_StyleInfo.OutlineColor());
			this->setOutlineThickness(m_StyleInfo.OutlineThickness());

			this->m_BoundingBox.PtA(position);
			this->m_BoundingBox.PtB(position + size);
		}
	}

	~SVGRectangle() 
	{ 
	}

	ObjectShape* CloneShape() const
	{
		return new Rectangle(*this);
	}
};


class SVGEllipse 
	: public SVGElement
	, public Ellipse
{
public:
	SVGEllipse(const XMLNode& node)
		: Ellipse()
		, SVGElement(node)
	{
		TPoint<float> position, radius;
		for (unsigned int i = 0; i < node.AttributeCount(); ++i)
		{
			const XMLAttribute* pAttr = node.GetAttribute(i);
			if (pAttr != nullptr)
			{
				if (pAttr->Description() == SVG::Element::AttrID::CenterX)
					position.x = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::CenterY)
					position.y = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::RadiusX)
					radius.x = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::RadiusY)
					radius.y = TStringConvert<float>(pAttr->Value());
			}
		}

		if (radius.x == 0 || radius.y == 0)
			m_bIsValid = false;
		else
		{
			this->setPosition(position);
			this->setRadius(radius);
			this->setFillColor(m_StyleInfo.FillColor());
			this->setOutlineColor(m_StyleInfo.OutlineColor());
			this->setOutlineThickness(m_StyleInfo.OutlineThickness());

			this->m_BoundingBox.PtA(position - radius);
			this->m_BoundingBox.PtB(position + radius);
		}
	}

	SVGEllipse(std::string cx, std::string cy, std::string rx, std::string ry)
	{
		TPoint<float> radius(0.0f, 0.0f);
		TPoint<float> position(0.0f, 0.0f);
		if (cx.length() > 0)
		{
			std::stringstream ssCX(cx); 
			ssCX >> position.x;
		}
		if (cy.length() > 0)
		{
			std::stringstream ssCY(cy); 
			ssCY >> position.y;
		}
		if (rx.length() > 0)
		{
			std::stringstream ssRX(rx); 
			ssRX >> radius.x;
		}
		if (ry.length() > 0)
		{
			std::stringstream ssRY(ry); 
			ssRY >> radius.y;
		}
	}

	~SVGEllipse() 
	{ 
	}

	ObjectShape* CloneShape() const
	{
		return new Ellipse(*this);
	}
};


class SVGCircle 
	: public SVGElement
	, public Circle
{
public:
	SVGCircle(const XMLNode& node)
		: Circle()
		, SVGElement(node)
	{
		float radius = 0;
		TPoint<float> position(0.0f, 0.0f);
		for (unsigned int i = 0; i < node.AttributeCount(); ++i)
		{
			const XMLAttribute* pAttr = node.GetAttribute(i);
			if (pAttr != nullptr)
			{
				if (pAttr->Description() == SVG::Element::AttrID::CenterX)
					position.x = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::CenterY)
					position.y = TStringConvert<float>(pAttr->Value());
				else if (pAttr->Description() == SVG::Element::AttrID::Radius)
					radius = TStringConvert<float>(pAttr->Value());
			}
		}

		if (radius == 0.0)
			m_bIsValid = false;
		else
		{
			this->setRadius(radius);
			this->setPosition(position);
			this->setFillColor(m_StyleInfo.FillColor());
			this->setOutlineColor(m_StyleInfo.OutlineColor());
			this->setOutlineThickness(m_StyleInfo.OutlineThickness());

			this->m_BoundingBox.PtA(TPoint<float>(position.x - radius, position.y - radius));
			this->m_BoundingBox.PtB(TPoint<float>(position.x + radius, position.y + radius));
		}
	}

	SVGCircle(std::string cx, std::string cy, std::string r) 
	{
		float radius = 0;
		TPoint<float> position(0.0f, 0.0f);
		if (cx.length() > 0)
		{
			std::stringstream ssCX(cx); 
			ssCX >> position.x;
		}
		if (cy.length() > 0)
		{
			std::stringstream ssCY(cy); 
			ssCY >> position.y;
		}
		if (r.length() > 0)
		{
			std::stringstream ssR(r); 
			ssR >> radius;
		}

		if (radius == 0.0)
			m_bIsValid = false;
		else
		{
			this->setRadius(radius);
			this->setPosition(position);
			this->setFillColor(m_StyleInfo.FillColor());
			this->setOutlineColor(m_StyleInfo.OutlineColor());
			this->setOutlineThickness(m_StyleInfo.OutlineThickness());

			this->m_BoundingBox.PtA(TPoint<float>(position.x - radius, position.y - radius));
			this->m_BoundingBox.PtB(TPoint<float>(position.x + radius, position.y + radius));
		}
	}

	~SVGCircle() 
	{ 
	}

	ObjectShape* CloneShape() const
	{
		return new Circle(*this);
	}
};


class SVGPolygon 
	: public SVGElement
	, public Polygon
{
public:
	SVGPolygon(const XMLNode& node)
		: SVGElement(node)
	{
		for (unsigned int i = 0; i < node.AttributeCount(); ++i)
		{
			const XMLAttribute* pAttr = node.GetAttribute(i);
			if (pAttr != nullptr)
			{
				if (pAttr->Description() == SVG::Element::AttrID::Points)
					FillPoints(pAttr->Value());
			}
		}

		if (m_bIsValid)
		{
			this->setFillColor(m_StyleInfo.FillColor());
			this->setOutlineColor(m_StyleInfo.OutlineColor());
			this->setOutlineThickness(m_StyleInfo.OutlineThickness());
		}
	}

	bool FillPoints(const std::string& points) 
	{
		unsigned int origPointCount = getPointCount();

		int startInd = 0; 
		int spaceInd = points.find(" ");
		while (spaceInd != std::string::npos)
		{
			std::string point = points.substr(startInd, spaceInd - startInd);
			if (point.length() > 0)
			{
				int commaPos = point.find(",");
				assert(commaPos != std::string::npos);
				if (commaPos != std::string::npos)
				{
					std::string ptX = point.substr(0, commaPos);
					std::string ptY = point.substr(commaPos + 1, point.length() - (commaPos + 1));
					std::stringstream ssPointX(ptX); 
					std::stringstream ssPointY(ptY);
				
					TPoint<float> pt;
					ssPointX >> pt.x;
					ssPointY >> pt.y;
					addPoint(pt);
				}
			}

			startInd += point.length() + 1;
			spaceInd = points.find(' ', startInd);
		}

		return (getPointCount() > origPointCount);
	}

	~SVGPolygon() 
	{ 
	}

	ObjectShape* CloneShape() const
	{
		return new Polygon(*this);
	}
};


class SVGPolyLine 
	: public SVGElement
	, public PolyLine
{
public:
	SVGPolyLine(const XMLNode& node)
		: PolyLine()
		, SVGElement(node)
	{
		for (unsigned int i = 0; i < node.AttributeCount(); ++i)
		{
			const XMLAttribute* pAttr = node.GetAttribute(i);
			if (pAttr != nullptr)
			{
				if (pAttr->Description() == SVG::Element::AttrID::Points)
					FillPoints(pAttr->Value());
			}
		}

		if (m_bIsValid)
		{
			this->setFillColor(m_StyleInfo.FillColor());
			this->setOutlineColor(m_StyleInfo.OutlineColor());
			this->setOutlineThickness(m_StyleInfo.OutlineThickness());
		}
	}

	bool FillPoints(const std::string& points) 
	{
		unsigned int origPointCount = getPointCount();

		int startInd = 0; 
		int spaceInd = points.find(" ");

		while (spaceInd != std::string::npos)
		{
			std::string point = points.substr(startInd, spaceInd - startInd);
			if (point.length() > 0)
			{
				int commaPos = point.find(",");
				assert(commaPos != std::string::npos);
				if (commaPos != std::string::npos)
				{
					std::string ptX = point.substr(0, commaPos);
					std::string ptY = point.substr(commaPos + 1, point.length() - (commaPos + 1));
					std::stringstream ssPointX(ptX); 
					std::stringstream ssPointY(ptY);
				
					TPoint<float> pt;
					ssPointX >> pt.x;
					ssPointY >> pt.y;
					addPoint(pt);
				}
			}

			startInd += point.length() + 1;
			spaceInd = points.find(' ', startInd);
		}

		return (getPointCount() > origPointCount);
	}

	~SVGPolyLine() 
	{ 
	}

	ObjectShape* CloneShape() const
	{
		return new PolyLine(*this);
	}
};

#endif // __SVG_ELEMENT_H