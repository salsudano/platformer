#ifndef __T_RECT_H
#define __T_RECT_H

#include <assert.h>
#include <SFML/Graphics.hpp>

#include "util/utils.h"
#include "util/t_point.h"

namespace Rect
{
	enum Feature
	{
		NoFeature		  =		 (0),

		Center			  = (1 << 0),
		
		TopSide			  = (1 << 1),
		LeftSide		  = (1 << 2),
		BottomSide		  = (1 << 3),
		RightSide		  = (1 << 4),

		TopLeftCorner     = (TopSide	| LeftSide),
		TopRightCorner    = (TopSide	| RightSide),
		BottomLeftCorner  = (BottomSide | LeftSide),
		BottomRightCorner = (BottomSide | RightSide)
	};

	enum SnapType
	{
		ClosestPt = 0,
		CenterPt  = 1
	};
};

DECLARE_BITWISE_OPERATORS( Rect::Feature );

template<class T> class TRect
{
friend class TPoint<T>;
public:
	TRect()
		: m_ptA(static_cast<T>(0), static_cast<T>(0))
		, m_ptB(static_cast<T>(0), static_cast<T>(0))
	{ }
	
	TRect(T left_x1, T top_y1, T right_x2, T bottom_y2)
		: m_ptA(left_x1, top_y1)
		, m_ptB(right_x2, bottom_y2)
	{
		Normalize();
	}

	TRect(const TRect<T>& r)
		: m_ptA(r.PtA())
		, m_ptB(r.PtB())
	{
		Normalize();
	}

	template<typename R>
	TRect(const sf::Rect<R>& r)
		: m_ptA(static_cast<T>(r.left), 
				static_cast<T>(r.top))
		, m_ptB(static_cast<T>(r.left + r.width), 
				static_cast<T>(r.top  + r.height))
	{ }

	TRect(const TPoint<T>& topLeft, const TPoint<T>& bottomRight)
		: m_ptA(topLeft)
		, m_ptB(bottomRight)
	{
		Normalize();
	}

	template<class D>
	TRect(const T x, const T y, const D height, const D width, const Rect::Feature origin)
	{
		Reset(x, y, height, width, origin);
	}

	template<class D>
	TRect(const TPoint<T>& pt, const D height, const D width, const Rect::Feature origin = Rect::TopLeftCorner)
	{
		Reset(pt.x, pt.y, height, width, origin);
	}

	bool operator == (const TRect<T>& rhs) const
	{
		return m_ptA == rhs.m_ptA 
			&& m_ptB == rhs.m_ptB;
	}

	bool operator != (const TRect<T>& rhs) const
	{
		return !this->operator==(rhs);
	}

	bool operator < (const TRect<T>& rhs) const
	{
		return m_ptA < rhs.m_ptA
			&& m_ptB < rhs.m_ptB;
	}

	bool operator > (const TRect<T>& rhs) const
	{
		return !this->operator<(rhs);
	}

	bool operator <= (const TRect<T>& rhs) const
	{
		return !this->operator>(rhs);
	}

	bool operator >= (const TRect<T>& rhs) const
	{
		return !this->operator<(rhs);
	}

	template<typename U>
	TRect<T>& operator = (const TRect<U>& rhs)
	{
		m_ptA = rhs.PtA();
		m_ptB = rhs.PtB();
		return *this;
	}

	TRect<T> operator + (const TRect<T>& rhs)
	{
		return TRect<T>(m_ptA + rhs.m_ptA, m_ptB + rhs.m_ptB);
	}

	TRect<T> operator - (const TRect<T>& rhs)
	{
		return TRect<T>(m_ptA - rhs.m_ptA, m_ptB - rhs.m_ptB);
	}

	TRect<T>& operator += (const TRect<T>& rhs)
	{
		m_ptA += rhs.m_ptA;
		m_ptB += rhs.m_ptB;
		return *this;
	}

	TRect<T>& operator -= (const TRect<T>& rhs)
	{
		m_ptA -= rhs.m_ptA;
		m_ptB -= rhs.m_ptB;
		return *this;
	}

	TRect<T>& operator ++ () 
	{
		++m_ptA; ++m_ptB;
		return *this;
	}

	TRect<T> operator ++ (int) 
	{
		TRect<T> ret(*this);
		this->operator++();
		return ret;
	}

	TRect<T>& operator -- () 
	{
		--m_ptA; --m_ptB;
		return *this;
	}

	TRect<T> operator -- (int)
	{
		TRect<T> ret(*this);
		this->operator++();
		return ret;
	}

	friend std::ostream& operator << (std::ostream& os, const TRect<T>& pt)
	{
		os << "[" << m_ptA << " " << m_ptB << "]";
		return os;
	}

	template <typename R>
	operator TRect<R>()
	{
		TRect<R> ret;
		ret.PtA(static_cast<TPoint<R>>(m_ptA));
		ret.PtB(static_cast<TPoint<R>>(m_ptB));
		return ret;
	}

	const T Top()		const { return m_ptA.y; }
	const T Bottom()	const { return m_ptB.y; }
	const T Left()		const { return m_ptA.x; }
	const T Right()		const { return m_ptB.x; }
	const T Height()	const { return abs(m_ptA.y - m_ptB.y); }
	const T Width()		const { return abs(m_ptB.x - m_ptA.x); }
	const T Area()		const { return Width() * Height();     }

	const TPoint<T>& PtA()			const { return m_ptA; }
	const TPoint<T>& PtB()			const { return m_ptB; }
	const TPoint<T>& TopLeft()		const { return m_ptA; }
	const TPoint<T>& BottomRight()	const { return m_ptB; }

	TRect<T>& PtA(const T x, const T y)
	{
		m_ptA.x = x;
		m_ptA.y = y;
		return *this;
	}

	TRect<T>& PtB(const T x, const T y)
	{
		m_ptB.x = x;
		m_ptB.y = y;
		return *this;
	}

	TRect<T>& PtA(const sf::Vector2<T> pt)
	{
		m_ptA.x = pt.x;
		m_ptA.y = pt.y;
		return *this;
	}

	TRect<T>& PtB(const sf::Vector2<T> pt)
	{
		m_ptB.x = pt.x;
		m_ptB.y = pt.y;
		return *this;
	}

	sf::Vector2<T> Size() const
	{
		sf::Vector2<T> size;
		size.x = this->Width();
		size.y = this->Height();
	}

	template<typename S>
	sf::Vector2<T> Size() const
	{
		sf::Vector2<S> size;
		size.x = static_cast<S>(this->Width());
		size.y = static_cast<S>(this->Height());
	}

	bool IsEmpty() const
	{
		return ((m_ptA.x == static_cast<T>(0)) &&
				(m_ptA.y == static_cast<T>(0)) &&
				(m_ptB.x == static_cast<T>(0)) &&
				(m_ptB.y == static_cast<T>(0)));
	}
	
	TPoint<T> Center() const
	{
		assert(this->IsNormalized());
		return sf::Vector2<T>(m_ptA.x + (Width()  / static_cast<T>(2)),
							  m_ptA.y + (Height() / static_cast<T>(2)));
	}

	void SetCenter(const TPoint<T> pt)
	{
		this->SetCenter(pt.x, pt.y);
	}

	void SetCenter(const T x, const T y)
	{
		m_ptA.x = x - static_cast<T>(static_cast<float>(this->Width())  / 2.0f);
		m_ptA.y = y - static_cast<T>(static_cast<float>(this->Height()) / 2.0f);
		m_ptB.x = x + static_cast<T>(static_cast<float>(this->Width())  / 2.0f);
		m_ptB.y = y + static_cast<T>(static_cast<float>(this->Height()) / 2.0f);
		this->Normalize();
	}

	bool IsNormalized() const
	{
		return m_ptA.x <= m_ptB.x 
			&& m_ptA.y <= m_ptB.y;
	}

	TRect<T>& Normalize()
	{
		if (m_ptA.x > m_ptB.x)
			TSwap(m_ptA.x, m_ptB.x);
		if (m_ptA.y > m_ptB.y)
			TSwap(m_ptA.y, m_ptB.y);
		return *this;
	}

	TRect<T> Normalized() const
	{
		if (this->IsNormalized())
			return *this;
		return TRect<T>(*this);
	}

	template<typename Point>
	TRect<T>& Include(const Point& pt)
	{
		if (m_ptA.x > pt.x)
			m_ptA.x = pt.x;
		if (m_ptB.x < pt.x)
			m_ptB.x = pt.x;
		if (m_ptA.y > pt.y)
			m_ptA.y = pt.y;
		if (m_ptB.y < pt.y)
			m_ptB.y = pt.y;
		return *this;
	}

	TRect<T>& Include(const TRect<T>& rect)
	{
		this->Include(rect.m_ptA);
		this->Include(rect.m_ptB);
		return *this;
	}

	void Reset() 
	{ 
		m_ptA.Reset();
		m_ptB.Reset();
	}

	template<class D>
	void Reset(const T x, const T y, const D height, const D width, const Rect::Feature origin)
	{
		switch (origin)
		{
			// If pt is the top-left of the rect...
			case Rect::TopLeftCorner:
				m_ptA.x = x;
				m_ptA.y = y;
				m_ptB.x = x + static_cast<T>(width);
				m_ptB.y = y + static_cast<T>(height);
				break;

			// If pt is the bottom-right of the rect...
			case Rect::BottomRightCorner:
				m_ptA.x = x - static_cast<T>(width);
				m_ptA.y = y - static_cast<T>(height);
				m_ptB.x = x;
				m_ptB.y = y;
				break;

			// If pt is the center of the rect...
			case Rect::Center:
				m_ptA.x = x - static_cast<T>(static_cast<float>(width)  / 2.0f);
				m_ptA.y = y - static_cast<T>(static_cast<float>(height) / 2.0f);
				m_ptB.x = x + static_cast<T>(static_cast<float>(width)  / 2.0f);
				m_ptB.y = y + static_cast<T>(static_cast<float>(height) / 2.0f);
				break;
		}

		this->Normalize();
	}

	void SetHeight(T newHeight, const Rect::Feature fromSide = Rect::TopLeftCorner)
	{
		if (Height() != newHeight)
		{
			switch (fromSide)
			{
				case Rect::Center:
					m_ptA.y = (Center().y - (newHeight / static_cast<T>(2)));
					m_ptB.y = (m_ptA.y + newHeight);
					break;
				case Rect::BottomSide:
					m_ptA.y = (m_ptB.y - newHeight);
					break;
				default:
				case Rect::TopSide:
					m_ptB.y = (m_ptA.y + newHeight);
					break;
			}
		}
	}
	
	void SetWidth(T newWidth, const Rect::Feature fromSide = Rect::TopLeftCorner)
	{
		if (Width() != newWidth)
		{
			switch (fromSide)
			{
				case Rect::Center:
					m_ptA.x = Center().x - (newWidth / static_cast<T>(2));
					m_ptB.x = m_ptA.x + newWidth;
					break;
				case Rect::RightSide:
					m_ptA.x = (m_ptB.x - newWidth);
					break;
				default:
				case Rect::LeftSide:
					m_ptB.x = (m_ptA.x + newWidth);
					break;
			}
		}
	}

	TRect<T>& RescaleSelf(const float xScale, const float yScale, const Rect::Feature fromHere)
	{
		this->SetHeight(Height() * yScale, fromHere);
		this->SetWidth(Width() * xScale, fromHere);
		return *this;
	}

	TRect<T> Rescale(const float scale, const Rect::Feature fromHere)
	{
		TRect<T> ret(*this);
		ret.RescaleSelf(scale, scale, fromHere);
		return ret;
	}

	TRect<T> Rescale(const float xScale, const float yScale, const Rect::Feature fromHere)
	{
		TRect<T> ret(*this);
		ret.RescaleSelf(xScale, yScale, fromHere);
		return ret;
	}

	TRect<T>& Expand(const T val)
	{
		Expand(val, val);
	}

	TRect<T>& Expand(const T dx, const T dy)
	{
		m_ptA.x -= dx;
		m_ptA.y -= dy;
		m_ptB.x += dx;
		m_ptB.y += dy;
		return Normalize();
	}

	TRect<T>& Move(const sf::Vector2<T>& moveOffset)
	{
		return Move(moveOffset.x, moveOffset.y);
	}

	TRect<T>& Move(const T dx, const T dy)
	{
		m_ptA.x += dx;
		m_ptB.x += dx;
		m_ptA.y += dy;
		m_ptB.y += dy;
		return *this;
	}

	TRect<T>& MoveUp(const T dy)
	{
		m_ptA.y -= dy;
		m_ptB.y -= dy;
		return *this;
	}

	TRect<T>& MoveDown(const T dy)
	{
		m_ptA.y += dy;
		m_ptB.y += dy;
		return *this;
	}

	TRect<T>& MoveLeft(const T dx)
	{
		m_ptA.x -= dx;
		m_ptB.x -= dx;
		return *this;
	}

	TRect<T>& MoveRight(const T dx)
	{
		m_ptA.x += dx;
		m_ptB.x += dx;
		return *this;
	}

	bool Intersects(const TRect<T>& r) const
	{
		assert(this->IsNormalized() && r.IsNormalized());
		
		bool xOverlap = m_ptA.x >= r.m_ptA.x && m_ptA.x <= r.m_ptB.x ||
			            m_ptB.x >= r.m_ptA.x && m_ptB.x <= r.m_ptB.x ||
						r.m_ptA.x >= m_ptA.x && r.m_ptA.x <= m_ptB.x ||
			            r.m_ptB.x >= m_ptA.x && r.m_ptB.x <= m_ptB.x;

		bool yOverlap = m_ptA.y >= r.m_ptA.y && m_ptA.y <= r.m_ptB.y ||
			            m_ptB.y >= r.m_ptA.y && m_ptB.y <= r.m_ptB.y ||
						r.m_ptA.y >= m_ptA.y && r.m_ptA.y <= m_ptB.y ||
			            r.m_ptB.y >= m_ptA.y && r.m_ptB.y <= m_ptB.y;

		return (xOverlap && yOverlap);
	}

	const TRect<T> Intersection(const TRect<T>& r) const
	{
		assert(this->IsNormalized() && r.IsNormalized());

		TRect<T> intersection;
		if (this->Intersects(r))
		{
			if (r.Contains(m_ptA))
				intersection.m_ptA = m_ptA;
			else if (this->Contains(r.m_ptA))
				intersection.m_ptA = r.m_ptA;
			else
			{
				if (m_ptA.x == r.m_ptA.x || m_ptA.x == r.m_ptB.x)
					intersection.m_ptA.x = m_ptA.x;
				else if (r.m_ptA.x == m_ptA.x || r.m_ptA.x == m_ptB.x)
					intersection.m_ptA.x = r.m_ptA.x;
				else if (m_ptA.rightof(r.m_ptA) && m_ptA.leftof(r.m_ptB))
					intersection.m_ptA.x = m_ptA.x;
				else if (r.m_ptA.rightof(m_ptA) && r.m_ptA.leftof(m_ptB))
					intersection.m_ptA.x = r.m_ptA.x;
				else assert(false);

				if (m_ptA.y == r.m_ptA.y || m_ptA.y == r.m_ptB.y)
					intersection.m_ptA.y = m_ptA.y;
				else if (r.m_ptA.y == m_ptA.y || r.m_ptA.y == m_ptB.y)
					intersection.m_ptA.y = r.m_ptA.y;
				else if (m_ptA.below(r.m_ptA) && m_ptA.above(r.m_ptB))
					intersection.m_ptA.y = m_ptA.y;
				else if (r.m_ptA.below(m_ptA) && r.m_ptA.above(m_ptB))
					intersection.m_ptA.y = r.m_ptA.y;
				else assert(false);
			}

			if (r.Contains(m_ptB))
				intersection.m_ptB = m_ptB;
			else if (this->Contains(r.m_ptB))
				intersection.m_ptB = r.m_ptB;
			else
			{
				if (m_ptB.x == r.m_ptA.x || m_ptB.x == r.m_ptB.x)
					intersection.m_ptB.x = m_ptB.x;
				else if (r.m_ptB.x == m_ptA.x || r.m_ptB.x == m_ptB.x)
					intersection.m_ptB.x = r.m_ptB.x;
				else if (m_ptB.rightof(r.m_ptA) && m_ptB.leftof(r.m_ptB))
					intersection.m_ptB.x = m_ptB.x;
				else if (r.m_ptB.rightof(m_ptA) && r.m_ptB.leftof(m_ptB))
					intersection.m_ptB.x = r.m_ptB.x;
				else assert(false);

				if (m_ptB.y == r.m_ptA.y || m_ptB.y == r.m_ptB.y)
					intersection.m_ptB.y = m_ptB.y;
				else if (r.m_ptB.y == m_ptA.y || r.m_ptB.y == m_ptB.y)
					intersection.m_ptB.y = r.m_ptB.y;
				else if (m_ptB.below(r.m_ptA) && m_ptB.above(r.m_ptB))
					intersection.m_ptB.y = m_ptB.y;
				else if (r.m_ptB.below(m_ptA) && r.m_ptB.above(m_ptB))
					intersection.m_ptB.y = r.m_ptB.y;
				else assert(false);
			}
		}
		return intersection;
	}

	bool Contains(const TPoint<T>& pt) const
	{
		return this->Contains(pt.x, pt.y);
	}

	bool Contains(const T x, const T y) const
	{
		return m_ptA.x <= x    // rPt is right of ptA
			&& m_ptB.x >= x    // rPt is left of ptB
			&& m_ptA.y <= y    // rPt is below of ptA
			&& m_ptB.y >= y;   // rPt is above of ptB
	}

	bool Contains(const TRect<T>& r) const
	{
		return (((r.m_ptA.x >= m_ptA.x) && (r.m_ptA.x <= m_ptB.x)) && // r.ptA is right of ptA and left of ptB
				((r.m_ptB.x >= m_ptA.x) && (r.m_ptB.x <= m_ptB.x)) && // r.ptB is right of ptA and left of ptB
				((r.m_ptA.y >= m_ptA.y) && (r.m_ptA.y <= m_ptB.y)) && // r.ptA is below ptA and above of ptB
				((r.m_ptB.y >= m_ptA.y) && (r.m_ptB.y <= m_ptB.y)));  // r.ptB is below ptA and above of ptB
	}

	bool LeftOf(const TPoint<T>& pt)	 const { return (m_ptA.x < pt.x); }
	bool RightOf(const TPoint<T>& pt)	 const { return (m_ptB.x > pt.x); }
	bool HigherThan(const TPoint<T>& pt) const { return (m_ptA.y < pt.y); }
	bool LowerThan(const TPoint<T>& pt)  const { return (m_ptB.y > pt.y); }

	sf::Vector2<T> MoveToContain(const TRect<T>& rectToContain)
	{
		sf::Vector2<T> moveOffset;
		if (rectToContain.LeftOf(m_ptA))
			moveOffset.x = (rectToContain.m_ptA.x - m_ptA.x);
		else if (rectToContain.RightOf(m_ptB))
			moveOffset.x = (rectToContain.m_ptB.x - m_ptB.x);
		if (rectToContain.HigherThan(m_ptA))
			moveOffset.y = (rectToContain.m_ptA.y - m_ptA.y);
		else if (rectToContain.LowerThan(m_ptB))
			moveOffset.y = (rectToContain.m_ptB.y - m_ptB.y);
		
		this->Move(moveOffset);
		return moveOffset;
	}

	sf::Vector2<T> MoveToBeContainedIn(const TRect<T>& rectToBeContainedIn)
	{
		sf::Vector2<T> moveOffset;
		// Make sure *this fits in rect passed in...
		if (rectToBeContainedIn.Width()  > this->Width() && 
			rectToBeContainedIn.Height() > this->Height())
		{
			if (rectToBeContainedIn.PtA().leftof(m_ptA) && m_ptB.rightof(rectToBeContainedIn.PtB()))
				moveOffset.x = (rectToBeContainedIn.m_ptB.x - m_ptB.x); // move left
			else if (rectToBeContainedIn.PtB().rightof(m_ptB) && m_ptA.leftof(rectToBeContainedIn.PtA()))
				moveOffset.x = (rectToBeContainedIn.m_ptA.x - m_ptA.x); // move right
			
			if (rectToBeContainedIn.PtA().above(m_ptA) && m_ptB.below(rectToBeContainedIn.PtB()))
				moveOffset.y = (rectToBeContainedIn.m_ptB.y - m_ptB.y); // move up
			else if (rectToBeContainedIn.PtB().below(m_ptB) && m_ptA.above(rectToBeContainedIn.PtA()))
				moveOffset.y = (rectToBeContainedIn.m_ptA.y - m_ptA.y); // move down
		}

		this->Move(moveOffset);
		return moveOffset;
	}

	const sf::Rect<T> sfRect() const
	{
		return sf::Rect<T>(m_ptA.x, m_ptA.y, Width(), Height());
	}

	operator sf::RectangleShape() const
	{
		sf::RectangleShape rectShape( sf::Vector2<float>(
			static_cast<float>(Width()), static_cast<float>(Height())));
		rectShape.setPosition(m_ptA);
		return rectShape;
	}

private:
	TPoint<T> m_ptA; // top left
	TPoint<T> m_ptB; // bottom right
};

#endif // __T_RECT_H