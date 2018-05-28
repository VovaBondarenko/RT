#include "../../include/extra_function.h"

void	vec3_normalize(t_vec3 *vector)
{
	double		len;

	len = (sqrt(vector->x * vector->x + vector->y *
				vector->y + vector->z * vector->z));
	if (len != 0)
	{
		len = 1.0f / len;
		vector->x *= len;
		vector->y *= len;
		vector->z *= len;
	}
}
