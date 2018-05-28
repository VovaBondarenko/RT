#include "../../include/extra_function.h"

int	vec3_rotate(t_vec3 *vector, t_vec3 vec3_rotate)
{
	if (vec3_rotate.x)
		vec3_rot(vector, X, vec3_rotate.x);
	if (vec3_rotate.y)
		vec3_rot(vector, Y, vec3_rotate.y);
	if (vec3_rotate.z)
		vec3_rot(vector, Z, vec3_rotate.z);
	return (1);
}

int	vec3_inverse_rotate(t_vec3 *vector, t_vec3 vec3_rotate)
{
	if (vec3_rotate.z)
		vec3_rot(vector, Z, -vec3_rotate.z);
	if (vec3_rotate.y)
		vec3_rot(vector, Y, -vec3_rotate.y);
	if (vec3_rotate.x)
		vec3_rot(vector, X, -vec3_rotate.x);
	return (1);
}
