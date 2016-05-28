#ifndef __MATH_UTILS_H
#define __MATH_UTILS_H

template<class T>
bool TSwap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
	return true;
}

template<class T>
bool TSwap(T* p1, T* p2)
{
	if ((p1 != nullptr) && (p2 != nullptr))
	{
		T* pTemp = p1;
		p1 = p2;
		p2 = pTemp;
		return true;
	}
	return false;
}

template<class T> 
T TConvert(const float val) 
{	
	return static_cast<T>(val + 0.5f); 
}

#endif // __MATH_UTILS_H