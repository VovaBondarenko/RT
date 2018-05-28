#include "../../include/extra_function.h"

t_vec3	vec3_sub(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3 vector;

	vector.x = vector1.x - vector2.x;
	vector.y = vector1.y - vector2.y;
	vector.z = vector1.z - vector2.z;
	return (vector);
}
