#ifndef BASICMATH_H_
#define BASICMATH_H_

#ifndef M_PI
#define M_PI 3.14159265
#endif

template <class T> static inline void swap(T &a, T &b)
{
	T t = a;
	a = b;
	b = t;
}

template <class T> static inline T max(T a, T b)
{
	return a > b ? a : b;
}

template <class T> static inline T min(T a, T b)
{
	return a < b ? a : b;
}

template <class T> static inline T abs(T n)
{
	return n < 0 ? -n : n;
}

#endif
