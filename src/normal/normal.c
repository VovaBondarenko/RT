#include "../../include/rt.h"

t_vec3	chewing_gum_n(t_vec3 *vector, t_obj *obj)
{
	t_vec3	result;

	(void)obj;
	result.x = 4 * pow(vector->x, 3);
	result.y = 4 * pow(vector->y, 3);
	result.z = 4 * pow(vector->z, 3);
	return (result);
}

t_vec3	cube_hole_n(t_vec3 *vector, t_obj *obj)
{
	t_vec3	result;

	(void)obj;
	result.x = 4 * power(vector->x, 3) - 10 * vector->x;
	result.y = 4 * power(vector->y, 3) - 10 * vector->y;
	result.z = 4 * power(vector->z, 3) - 10 * vector->z;
	return (result);
}

t_vec3	hyperboloid_n(t_vec3 *vector, t_obj *obj)
{
	(void)obj;
	return ((t_vec3){vector->x, -vector->y, vector->z});
}

t_vec3	moebius_n(t_vec3 *vector, t_obj *obj)
{
	t_vec3	result;

	result.x = -2 * obj->scale * vector->z + 2 * vector->x *
		vector->y - 4 * vector->x * vector->z;
	result.y = -obj->scale2 + vector->x * vector->x + 3 * vector->y * vector->y
		- 4 * vector->y * vector->z + vector->z * vector->z;
	result.z = -2 * obj->scale * vector->x - 2 * vector->x * vector->x - 2
		* vector->y * vector->y + 2 * vector->y * vector->z;
	return (result);
}

t_vec3	paraboloid_n(t_vec3 *vector, t_obj *obj)
{
	t_vec3	result;

	result = *vector;
	result = vec3_sub(result, vec3_fmult(obj->dir, obj->scale));
	return (result);
}
