#include "../../include/rt.h"

t_vec3	selle_n(t_vec3 *vector, t_obj *obj)
{
	t_vec3	result;

	(void)obj;
	result.x = 2 * vector->x;
	result.z = -2 * vector->z;
	result.y = 1;
	return (result);
}

t_vec3	torus_n(t_vec3 *vector, t_obj *obj)
{
	t_vec3	result;

	result.x = 4 * vector->x * (vec3_dot(*vector, *vector) - (obj->torus_radius2
		+ obj->torus_radius1));
	result.y = 4 * vector->y * (vec3_dot(*vector, *vector) - (obj->torus_radius2
		+ obj->torus_radius1) + 2 * obj->torus_radius2);
	result.z = 4 * vector->z * (vec3_dot(*vector, *vector) - (obj->torus_radius2
		+ obj->torus_radius1));
	return (result);
}

t_vec3	sphere_n(t_vec3 *vector, t_obj *obj)
{
	(void)obj;
	return (*vector);
}

t_vec3	cylinder_n(t_vec3 *vector, t_obj *obj)
{
	t_vec3	result;

	result = *vector;
	result = vec3_sub(result, vec3_fmult(obj->dir, 1));
	return (result);
}
