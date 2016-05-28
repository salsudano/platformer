#ifndef __T_POINT_H
#define __T_POINT_H

#include <ostream>
#include <iomanip>
#include <type_traits>

#include <SFML/System/Vector2.hpp>

#include "util/math_utils.h"

template<class T>
class TPoint : public sf::Vector2<T>
{
public:	

	TPoint()		 : sf::Vector2<T>()		{ }
	TPoint(T x, T y) : sf::Vector2<T>(x, y) { }

	template <typename PointType>
	TPoint(const PointType& pt) 
		: sf::Vector2<T>(pt) 
	{ }

	void reset()
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);	
	}

	bool IsEmpty()						const { return (*this == TPoint<T>()); }

	bool leftof(const TPoint<T>& pt)	const { return (this->x < pt.x); }
	bool rightof(const TPoint<T>& pt)	const { return (this->x > pt.x); }
	bool above(const TPoint<T>& pt)		const { return (this->y < pt.y); }
	bool below(const TPoint<T>& pt)		const { return (this->y > pt.y); }
	
	void MoveUp(const T dy)		{ this->y -= dy; }
	void MoveDown(const T dy)	{ this->y += dy; }
	void MoveLeft(const T dx)	{ this->x -= dx; }
	void MoveRight(const T dx)	{ this->x += dx; }

	template <typename P>
	operator TPoint<P>()
	{
		TPoint<P> ret;
		ret.x = static_cast<P>(x);
		ret.y = static_cast<P>(y);
		return ret;
	}

	bool operator == (const TPoint<T>& rhs) const
	{
		return x == rhs.x 
			&& y == rhs.y;
	}

	bool operator != (const TPoint<T>& rhs) const
	{
		return !this->operator==(rhs);
	}

	bool operator < (const TPoint<T>& rhs) const
	{
		return x < rhs.x
			&& y < rhs.y;
	}

	bool operator > (const TPoint<T>& rhs) const
	{
		return !this->operator<(rhs);
	}

	bool operator <= (const TPoint<T>& rhs) const
	{
		return !this->operator>(rhs);
	}

	bool operator >= (const TPoint<T>& rhs) const
	{
		return !this->operator<(rhs);
	}

	template <typename U>
	TPoint<T>& operator = (const TPoint<U>& rhs)
	{
		if (!std::is_floating_point<T>::value && 
		     std::is_floating_point<U>::value)
		{
			x = static_cast<T>(rhs.x + 0.5f);
			y = static_cast<T>(rhs.y + 0.5f);
		}
		else
		{
			x = static_cast<T>(rhs.x);
			y = static_cast<T>(rhs.y);
		}
		return *this;
	}

	TPoint<T> operator + (const TPoint<T>& rhs)
	{
		return TPoint<T>(x + rhs.x, y + rhs.y);
	}

	TPoint<T> operator - (const TPoint<T>& rhs)
	{
		return TPoint<T>(x - rhs.x, y - rhs.y);
	}

	TPoint<T>& operator += (const TPoint<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	TPoint<T>& operator -= (const TPoint<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	TPoint<T>& operator ++ () 
	{
		++x; ++y;
		return *this;
	}

	TPoint<T> operator ++ (int) 
	{
		TPoint<T> ret(*this);
		this->operator++();
		return ret;
	}

	TPoint<T>& operator -- () 
	{
		--x; --y;
		return *this;
	}

	TPoint<T> operator -- (int)
	{
		TPoint<T> ret(*this);
		this->operator++();
		return ret;
	}

	friend std::ostream& operator << (std::ostream& os, const TPoint<T>& pt)
	{
		os << "(" 
		   << std::setw(5) << std::setprecision(3) 
		   << pt.x 
		   << std::setw(0)
		   << ", " 
		   << std::setw(5) << std::setprecision(3) 
		   << pt.y << ")";
		return os;
	}
};

#endif // __T_POINT_H