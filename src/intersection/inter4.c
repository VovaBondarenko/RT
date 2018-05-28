#include "../../include/rt.h"

#define RAY_X ray->dir.x
#define RAY_Z ray->dir.z

int		inside_check(double number)
{
	return ((number < -DELTA) ? -1 : (number > DELTA));
}

double	cube_hole(t_ray *ray, t_obj *object)
{
	double		a[5];
	double		roots[4];
	t_vec3		vector;
	int			result;

	object->in = INFINITY;
	object->out = INFINITY;
	vector = ray->pos;
	a[4] = power(RAY_X, 4) + power(ray->dir.y, 4) + power(RAY_Z, 4);
	a[3] = (4 * (power(RAY_X, 3) * vector.x + power(ray->dir.y, 3) * vector.y +
		power(RAY_Z, 3) * vector.z)) / a[4];
	a[2] = (6 * (power(RAY_X, 2) * power(vector.x, 2) + power(ray->dir.y, 2) *
		power(vector.y, 2) + power(RAY_Z, 2) * power(vector.z, 2)) -
		5 * vec3_dot(ray->dir, ray->dir)) / a[4];
	a[1] = (4 * (power(vector.x, 3) * RAY_X + power(vector.y, 3) * ray->dir.y +
		power(vector.z, 3) * RAY_Z) - 10 * vec3_dot(ray->dir, vector)) / a[4];
	a[0] = (power(vector.x, 4) + power(vector.y, 4) + power(vector.z, 4) -
		5 * vec3_dot(vector, vector) + object->scale) / a[4];
	result = solve_quartic(a, roots);
	if (result >= 2)
	{
		object->in = roots[0];
		object->out = roots[1];
	}
	return (root(roots, result));
}

double	chewing_gum(t_ray *ray, t_obj *object)
{
	int			result;
	t_vec3		vector;
	double		a[5];
	double		roots[4];

	object->in = INFINITY;
	object->out = INFINITY;
	vector = ray->pos;
	a[4] = power(RAY_X, 4) + power(ray->dir.y, 4) + power(RAY_Z, 4);
	a[3] = (4 * (power(RAY_X, 3) * vector.x + power(ray->dir.y, 3) * vector.y +
		power(RAY_Z, 3) * vector.z)) / a[4];
	a[2] = (6 * (power(RAY_X, 2) * power(vector.x, 2) + power(ray->dir.y, 2)
		* power(vector.y, 2) + power(RAY_Z, 2) * power(vector.z, 2))) / a[4];
	a[1] = (4 * (RAY_X * power(vector.x, 3) + ray->dir.y * power(vector.y, 3) +
		RAY_Z * power(vector.z, 3))) / a[4];
	a[0] = (power(vector.x, 4) + power(vector.y, 4) + power(vector.z, 4) -
		power(object->scale, 4)) / a[4];
	result = solve_quartic(a, roots);
	if (result >= 2)
	{
		object->in = roots[0];
		object->out = roots[1];
	}
	return (root(roots, result));
}

double	cylinder(t_ray *ray, t_obj *obj)
{
	double		a[3];
	double		roots[2];
	double		ro;
	double		lo;
	int			ret;

	obj->in = INFINITY;
	obj->out = INFINITY;
	vec3_normalize(&obj->dir);
	ro = vec3_dot(ray->dir, obj->dir);
	lo = vec3_dot(ray->pos, obj->dir);
	a[2] = 1.0 - ro * ro;
	a[1] = 2 * (vec3_dot(ray->dir, ray->pos) - ro * lo);
	a[0] = vec3_dot(ray->pos, ray->pos) - lo * lo - obj->scale * obj->scale;
	if (!(ret = solve_quadratic(a, roots)))
		return (INFINITY);
	obj->in = roots[0];
	obj->out = roots[1];
	if (obj->in < 0 && ((obj->in = obj->out) || 1))
		if (obj->in < 0)
			return (INFINITY);
	return (cone_check(ray, obj, vec3_is_zero(obj->cut_figure) ?
		obj->dir : obj->cut_figure));
}

double	plane(t_ray *ray, t_obj *object)
{
	t_calculation_coef	a;

	object->in = INFINITY;
	object->out = INFINITY;
	a.a = vec3_dot(object->dir, ray->dir);
	a.b = vec3_dot(object->dir, ray->pos);
	if (a.a == 0)
		return (INFINITY);
	a.coef = -a.b / a.a;
	if (a.coef > 0 && (object->in = a.coef))
		return (a.coef);
	else
		return (INFINITY);
}
