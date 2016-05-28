#ifndef __SVGDATA_H
#define __SVGDATA_H

#include <vector>

#include "util\svg_group.h"
#include "util\xml_document.h"
#include "util\t_rect.h"

class SVGData
{
public:
	SVGData();
	SVGData(const std::string& path)
	{
		XMLDocument xmlDoc(path);
		if (xmlDoc.IsSVGFile())
		{
			const XMLNode* pXMLRoot = xmlDoc.RootNode();
			if ((pXMLRoot != nullptr) && SetSVGRectData(*pXMLRoot))
			{
				if (pXMLRoot->HasAttribute(XML::Node::Attribute::ID))
					m_lsDataGroups.push_back(new SVGGroup(*pXMLRoot));
				else
				{
					for (unsigned int i = 0; i < pXMLRoot->ChildCount(); ++i)
					{
						const XMLNode* pGroupNode = pXMLRoot->GetChild(i);
						if (pGroupNode != nullptr)
							m_lsDataGroups.push_back(new SVGGroup(*pGroupNode));
					}
				}
			}
		}
	}

	~SVGData()
	{
		for (unsigned int i = 0; i < m_lsDataGroups.size(); ++i)
		{
			if (m_lsDataGroups[i] != nullptr)
				delete m_lsDataGroups[i];
			m_lsDataGroups[i] = nullptr;
		}
	}

	const std::vector<SVGGroup*>& DataGroups() const
	{
		return m_lsDataGroups;
	}

	const TRect<double>& Rect() const
	{
		return m_Rect;
	}

private:
	bool SetSVGRectData(const XMLNode& svgNode)
	{
		double x = 0.0, y = 0.0, width = 0.0, height = 0.0;
		for (unsigned int i = 0; i < svgNode.AttributeCount(); ++i)
		{
			const XMLAttribute* pSVGAttribute = svgNode.GetAttribute(i);
			if (pSVGAttribute != nullptr)
			{
				const std::string& val = pSVGAttribute->Value();
				int pxIndex = val.find(SVG::Element::AttrID::Pixel);
				if (pxIndex != std::string::npos)
				{
					std::stringstream ss(val.substr(0, pxIndex));
					if (pSVGAttribute->Description() == SVG::Element::AttrID::X)
						ss >> x;
					else if (pSVGAttribute->Description() == SVG::Element::AttrID::Y)
						ss >> y;
					else if (pSVGAttribute->Description() == SVG::Element::AttrID::Height)
						ss >> height;
					else if (pSVGAttribute->Description() == SVG::Element::AttrID::Width)
						ss >> width;
				}
			}
		}

		m_Rect = TRect<double>(x, y, height, width);
		return (!m_Rect.IsEmpty() && (m_Rect.Area() > 0.0));
	}

private:
	TRect<double>			m_Rect;
	std::vector<SVGGroup*>	m_lsDataGroups;
};

#endif // __SVGDATA_H