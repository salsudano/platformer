#ifndef __SVG_DEFS_H
#define __SVG_DEFS_H

namespace SVG
{
	namespace Element
	{
		namespace Descr
		{
			static const char* const Line				 = "line";
			static const char* const Path				 = "path";
			static const char* const Rectangle			 = "rect";
			static const char* const Circle				 = "circle";
			static const char* const Ellipse			 = "ellipse";
			static const char* const Polygon			 = "polygon";
			static const char* const Polyline			 = "polyline";
		};

		namespace AttrID
		{
			static const char* const ID					= "id";
			static const char* const Fill				= "fill";
			static const char* const StrokeColor		= "stroke";
			static const char* const StrokeWidth		= "stroke-width";
			static const char* const StrokeMiterLimit	= "stroke-miterlimit";
			static const char* const Height				= "height";
			static const char* const Width				= "width";
			static const char* const X					= "x";
			static const char* const Y					= "y";
			static const char* const X1					= "x1";
			static const char* const X2					= "x2";
			static const char* const Y1					= "y1";
			static const char* const Y2					= "y2";
			static const char* const CenterX			= "cx";
			static const char* const CenterY			= "cy";
			static const char* const Radius				= "r";
			static const char* const RadiusX			= "rx";
			static const char* const RadiusY			= "ry";
			static const char* const Points				= "points";
			static const char* const Pixel				= "px";
		};

		namespace ValueID
		{
			static const char* const None				= "none";
		};
	};

	namespace Stroke
	{
		namespace Opacity
		{
			enum Value
			{
				Transparent = 0,
				Solid		= 255
			};
		};
	};

	namespace PathData
	{
		namespace Type
		{
			enum Value
			{
				Invalid,
				MoveTo,
				ClosePath,
				LineTo,
				CubicBezier,
				QuadraticBezier,
				EllipticalArc
			};
		};

		namespace Position
		{
			enum Type
			{
				Invalid,
				Absolute,
				Relative
			};
		};
	};
};

#endif // __SVG_DEFS_H