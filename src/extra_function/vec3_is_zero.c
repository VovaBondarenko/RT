#include "../../include/extra_function.h"

int	vec3_is_zero(t_vec3 vector)
{
	if (vector.x == 0 &&
		vector.y == 0 &&
		vector.z == 0)
		return (1);
	return (0);
}
