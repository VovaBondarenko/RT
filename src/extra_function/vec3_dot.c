#include "../../include/extra_function.h"

double	vec3_dot(t_vec3 vector1, t_vec3 vector2)
{
	return (vector1.x * vector2.x +
			vector1.y * vector2.y +
			vector1.z * vector2.z);
}
