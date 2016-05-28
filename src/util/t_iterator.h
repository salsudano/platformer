#ifndef __T_ITERATOR_H
#define __T_ITERATOR_H

template<class T> class TIterator
{
public:
	TIterator()
		: m_bStopIterating(false)
		, m_ElemCount(0)
	{ }
	~TIterator() { }

	virtual void Do(const T& element) = 0;
	void ElementDo(const T& element)
	{
		m_ElemCount++;
		Do(element);
	}

	bool ShouldStop()
	{
		if (m_bStopIterating)
		{
			m_bStopIterating = false;
			return true;
		}
		return false; 
	}

	bool DoneIterating() 
	{
		m_bStopIterating; 
	}

public:
	bool	m_bStopIterating;
	int		m_ElemCount;
};

#endif // __T_ITERATOR_H