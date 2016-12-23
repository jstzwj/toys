#include"memloc.h"
inline void * memloc(__int64 space)
{
	if (space > 0)
	{
		return malloc(space);
	}
	else
	{
		abort();
	}
}