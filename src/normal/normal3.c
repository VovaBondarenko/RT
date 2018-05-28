#include "../../include/rt.h"

t_vec3	cone_n(t_vec3 *vector, t_obj *obj)
{
	t_vec3	result;

	result = *vector;
	result = vec3_sub(result,
			vec3_fmult(obj->dir, (1 + obj->tan_alfa) * 1));
	return (result);
}

t_vec3	plane_n(t_vec3 *vector, t_obj *obj)
{
	(void)vector;
	return (obj->dir);
}
