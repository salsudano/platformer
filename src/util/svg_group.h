#ifndef __SVG_GROUP_H
#define __SVG_GROUP_H

#include <vector>
#include <iostream>

#include "util\xml_document.h"
#include "util\svg_element.h"

class SVGGroup
{
public:
	SVGGroup(const XMLNode& node, SVGGroup* pParentGroup = nullptr)
		: m_pParent(pParentGroup)
	{
		const std::string& svgGroupType = node.Type();
		assert(svgGroupType == XML::Node::Type::DataGroup || 
			   svgGroupType == XML::Node::Type::SVG);
		if (this->SetAttributeData(node, pParentGroup))
		{
			for (unsigned int i = 0; i < node.ChildCount(); ++i)
			{
				const XMLNode* pChild = node.GetChild(i);
				if (pChild != nullptr)
					this->AddGroupDataElements(*pChild, this);
			}
		}
	}
	
	~SVGGroup() 
	{
		for (unsigned int i = 0; i < m_lsElements.size(); ++i)
		{
			if (m_lsElements[i] != nullptr)
				delete m_lsElements[i];
			m_lsElements[i] = nullptr;
		}
		for (unsigned int i = 0; i < m_lsDataGroups.size(); ++i)
		{
			if (m_lsDataGroups[i] != nullptr)
				delete m_lsDataGroups[i];
			m_lsDataGroups[i] = nullptr;
		}
	}

	const SVGGroup* ParentGroup() const
	{
		return m_pParent;
	}

	const std::vector<SVGGroup*>& DataGroups() const 
	{
		return m_lsDataGroups;
	}

	const std::vector<SVGElement*>& Elements() const
	{
		return m_lsElements;
	}

	const std::string& LayerType() const
	{
		return m_LayerType;
	}

private:
	bool AddGroupDataElements(const XMLNode& node, SVGGroup* pParentGroup = nullptr)
	{
		if (node.Type() == XML::Node::Type::DataGroup)
		{
			m_lsDataGroups.push_back(new SVGGroup(node, pParentGroup));
			return true;
		}
		else
		{
			SVGElement* pSVGElement = this->ConstructSVGElementFromXMLNode(node);
			if (pSVGElement != nullptr)
			{
				m_lsElements.push_back(pSVGElement);
				return true;
			}
		}

		return false;
	}

	SVGElement* ConstructSVGElementFromXMLNode(const XMLNode& node)
	{
		SVGElement* pRet = nullptr;

		ShapeType dataType = this->GetElementShapeType(node.Type());
		switch (dataType)
		{
			case ShapeType::Circle:
				pRet = new SVGCircle(node);
				break;
			case ShapeType::Ellipse:
				pRet = new SVGEllipse(node);
				break;
			case ShapeType::Line:
				pRet = new SVGLine(node);
				break;
//			case ShapeType::Path:
//				pRet = new SVGPath(node);
//				break;
			case ShapeType::Polygon:
				pRet = new SVGPolygon(node);
				break;
			case ShapeType::PolyLine:
				pRet = new SVGPolyLine(node);
				break;
			case ShapeType::Rectangle:
				pRet = new SVGRectangle(node);
				break;
		}

		return pRet;
	}

	bool SetAttributeData(const XMLNode& node, SVGGroup* pParentGroup)
	{
		m_LayerType = "";

		for (unsigned int i = 0; i < node.AttributeCount() && (m_LayerType.length() == 0); ++i)
		{
			const XMLAttribute* pAttr = node.GetAttribute(i);
			if ((pAttr != nullptr) && (pAttr->Description() == XML::Node::Attribute::ID))
				m_LayerType = pAttr->Value();
		}

		if ((m_LayerType.length() == 0) && 
			(node.ChildCount() > 0) &&
			(pParentGroup != nullptr) )
		{
			const std::string& parentLayerType = pParentGroup->LayerType();
			if (parentLayerType.length() > 0)
				m_LayerType = parentLayerType + "SubGroup";
		}

		return (m_LayerType.length() > 0);
	}

	ShapeType GetElementShapeType(const std::string& type)
	{
		if (type == SVG::Element::Descr::Circle)
			return ShapeType::Circle;
		else if (type == SVG::Element::Descr::Ellipse)
			return ShapeType::Ellipse;
		else if (type == SVG::Element::Descr::Line)
			return ShapeType::Line;
		else if (type == SVG::Element::Descr::Path)
			return ShapeType::Path;
		else if (type == SVG::Element::Descr::Polygon)
			return ShapeType::Polygon;
		else if (type == SVG::Element::Descr::Polyline)
			return ShapeType::PolyLine;
		else if (type == SVG::Element::Descr::Rectangle)
			return ShapeType::Rectangle;
		return ShapeType::Invalid;
	}

private:
	const SVGGroup*	const	 m_pParent;
	std::string				 m_LayerType;
	std::vector<SVGGroup*>	 m_lsDataGroups;
	std::vector<SVGElement*> m_lsElements;
};

#endif // __SVG_GROUP_H