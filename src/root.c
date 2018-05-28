#include "../include/rt.h"

double	root(double *r, int n)
{
	short	i;

	i = 0;
	while (i < n)
	{
		if (r[i] > DELTA)
			return (r[i]);
		i++;
	}
	return (INFINITY);
}
