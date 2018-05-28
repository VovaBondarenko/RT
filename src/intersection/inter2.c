#include "../../include/rt.h"

#define OBJ obj->cut_figure

double	paraboloid(t_ray *ray, t_obj *obj)
{
	double	a[7];
	t_vec3	vector;
	int		result;

	obj->in = INFINITY;
	obj->out = INFINITY;
	vector = ray->pos;
	a[6] = vec3_dot(vector, obj->dir);
	a[5] = vec3_dot(ray->dir, obj->dir);
	a[2] = vec3_dot(ray->dir, ray->dir) - a[5] * a[5];
	a[1] = 2 * (vec3_dot(ray->dir, vector) - a[5] * (a[6] + 2 * obj->scale));
	a[0] = vec3_dot(vector, vector) - a[6] * (a[6] + 4 * obj->scale);
	if (!(result = solve_quadratic(a, &a[3])))
		return (INFINITY);
	obj->in = a[3];
	obj->out = a[4];
	if (obj->in < 0)
	{
		obj->in = obj->out;
		if (obj->out < 0)
			return (INFINITY);
	}
	return (cone_check(ray, obj,
			vec3_is_zero(obj->cut_figure) ? obj->dir : obj->cut_figure));
}

double	hyperboloid(t_ray *ray, t_obj *obj)
{
	double	a[3];
	double	roots[2];
	int		result;
	t_vec3	vector;

	obj->in = INFINITY;
	obj->out = INFINITY;
	vector = ray->pos;
	a[2] = ray->dir.x * ray->dir.x - ray->dir.y * ray->dir.y +
		ray->dir.z * ray->dir.z;
	a[1] = 2 * (vector.x * ray->dir.x - vector.y * ray->dir.y +
		vector.z * ray->dir.z);
	a[0] = vector.x * vector.x - vector.y * vector.y +
		vector.z * vector.z - obj->scale2;
	if (!(result = solve_quadratic(a, roots)))
		return (INFINITY);
	obj->in = roots[0];
	obj->out = roots[1];
	if (obj->in < DELTA)
	{
		obj->in = obj->out;
		if (obj->in < DELTA)
			return (INFINITY);
	}
	return (cone_check(ray, obj, vec3_is_zero(OBJ) ? obj->dir : OBJ));
}
