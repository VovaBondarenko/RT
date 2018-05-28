#include "../../include/extra_function.h"

t_vec3i	vec3_convert(t_vec3 vec3)
{
	t_vec3i vector;

	vector.x = (int)vec3.x;
	vector.y = (int)vec3.y;
	vector.z = (int)vec3.z;
	return (vector);
}
