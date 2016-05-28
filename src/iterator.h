#ifndef __ITERATOR_H
#define __ITERATOR_H

template<class T>
class Iterator
{
public:
					Iterator();
	virtual		   ~Iterator();

	virtual bool	Do(T& rObj)
	virtual bool	Do(const T& rObj)

private:
	bool			m_bIterating;
};

#endif // __ITERATOR_H