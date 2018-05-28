#include "../../include/extra_function.h"

t_vec3	vec3_fmult(t_vec3 vector1, double arg)
{
	t_vec3 vector;

	vector.x = vector1.x * arg;
	vector.y = vector1.y * arg;
	vector.z = vector1.z * arg;
	return (vector);
}
