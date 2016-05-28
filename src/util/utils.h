#ifndef __UTILS_H
#define __UTILS_H

// Prints to visual studio output console
#include <ostream>
#define VSConsolePrint( s )                 \
{                                           \
   std::ostringstream os_;                  \
   os_ << s;                                \
   OutputDebugString( os_.str().c_str() );  \
}

// Declares and defines bitwise operators for the passed in (enum) type
#define DECLARE_BITWISE_OPERATORS( T ) 	                                                               \
inline T operator &  (T  a, T b) { return static_cast<T>(static_cast<int>(a) & static_cast<int>(b)); } \
inline T operator &= (T& a, T b) { return a = a & b; }                                                 \
inline T operator |  (T  a, T b) { return static_cast<T>(static_cast<int>(a) | static_cast<int>(b)); } \
inline T operator |= (T& a, T b) { return a = a | b; }                                                 \


#endif // __UTILS_H