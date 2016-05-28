#ifndef __OBJECT_STYLE_H
#define __OBJECT_STYLE_H

#include <string>
#include <sstream>
#include <SFML\Graphics\Color.hpp>

#include "util\svg_defs.h"

class ObjectStyle
{
public:
	ObjectStyle() 
		: m_FillColor(0, 0, 0, 255)
		, m_OutlineColor(0, 0, 0, 255)
		, m_OutlineThickness(0)
		, m_OutlineMiterLimit(0)
	{ }

	virtual ~ObjectStyle() 
	{ 
	}

	const sf::Color& OutlineColor()		 const	{ return m_OutlineColor;	  }
	const sf::Color& FillColor()		 const	{ return m_FillColor;		  }
	const float		 OutlineThickness()	 const	{ return m_OutlineThickness;  }
	const float		 OutlineMiterLimit() const	{ return m_OutlineMiterLimit; }

	void OutlineColor(const std::string& color)	{ m_OutlineColor = SetColor(color);	}
	void FillColor(const std::string& color)	{ m_FillColor	 = SetColor(color);	}
	void OutlineThickness(float thickness)		{ m_OutlineThickness = thickness;	}

	void OutlineThickness(const std::string& outlineWidth)
	{
		m_OutlineThickness = 0;
		if (outlineWidth.length() > 0)
		{
			std::stringstream ss(outlineWidth);
			ss >> m_OutlineThickness;
		}
	}

	void OutlineMiterLimit(const std::string& miterLimit)
	{
		m_OutlineMiterLimit = 0;
		if (miterLimit.length() > 0)
		{
			std::stringstream ss(miterLimit);
			ss >> m_OutlineMiterLimit;
		}
	}

private:
	sf::Color SetColor(const std::string& color, const std::string& opacity = "1.0")
	{
		sf::Color ret;

		if ((color != SVG::Element::ValueID::None) && (color.find("#") == 0) && (color.length() == 7))
		{
			double opacityPercent = 0.0;
			int red = 0, green = 0, blue = 0;

			std::stringstream ssOpacity(opacity);
			std::stringstream ssRed(color.substr(1, 2));
			std::stringstream ssGreen(color.substr(3, 2));
			std::stringstream ssBlue(color.substr(5, 2));
			
			ssRed     >> std::hex >> red;
			ssGreen   >> std::hex >> green;
			ssBlue	  >> std::hex >> blue;
			ssOpacity >> opacityPercent;

			ret.r = red;
			ret.g = green;
			ret.b = blue;
			ret.a = static_cast<unsigned char>(opacityPercent * SVG::Stroke::Opacity::Solid);
		}

		return ret;
	}

private:
	sf::Color	m_FillColor;
	sf::Color	m_OutlineColor;
	float		m_OutlineThickness;
	float		m_OutlineMiterLimit;
};


#endif // __OBJECT_STYLE_H