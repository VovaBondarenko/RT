#include "../../include/extra_function.h"

t_vec3	vec3_scale(t_vec3 vector, double scale)
{
	vec3_normalize(&vector);
	vector.x *= scale;
	vector.y *= scale;
	vector.z *= scale;
	return (vector);
}
