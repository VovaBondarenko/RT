#include "../../include/rt.h"

double	cone_check(t_ray *ray, t_obj *object, t_vec3 vector)
{
	double	point;
	double	coef;

	coef = 0;
	point = vec3_dot(ray->dir, vector) * object->in +
		vec3_dot(ray->pos, vector);
	if (point > object->max || point < object->min)
	{
		object->in = object->out;
		object->out = INFINITY;
		point = vec3_dot(ray->dir, vector) * object->in +
			vec3_dot(ray->pos, vector);
		if (point < object->max && point > object->min && ((coef = point) || 1))
			return (object->in);
		else if ((object->in = INFINITY))
			return (INFINITY);
	}
	coef = point;
	return (object->in);
}

double	cone(t_ray *ray, t_obj *object)
{
	double	a[5];
	double	roots[2];

	object->in = INFINITY;
	object->out = INFINITY;
	a[4] = vec3_dot(ray->pos, object->dir);
	a[3] = vec3_dot(ray->dir, object->dir);
	a[2] = 1.0 - (1 + object->tan_alfa) * a[3] * a[3];
	a[1] = 2 * (vec3_dot(ray->dir, ray->pos) - (1 + object->tan_alfa) *
		a[3] * a[4]);
	a[0] = vec3_dot(ray->pos, ray->pos) - (1 + object->tan_alfa) * a[4] * a[4];
	if (!(solve_quadratic(a, roots)))
		return (INFINITY);
	object->in = roots[0];
	object->out = roots[1];
	if (object->in < 0)
	{
		object->in = object->out;
		if (object->out < 0)
			return (INFINITY);
	}
	return (cone_check(ray, object,
			vec3_is_zero(object->cut_figure) ? object->dir :
			object->cut_figure));
}

double	sphere(t_ray *ray, t_obj *object)
{
	t_calculation_coef	a;

	object->in = INFINITY;
	object->out = INFINITY;
	a.length = ray->pos;
	a.b = vec3_dot(a.length, ray->dir);
	a.c = vec3_dot(a.length, a.length) - object->scale2;
	a.discriminant = a.b * a.b - a.c;
	if (a.discriminant < DELTA)
		return (INFINITY);
	a.discriminant = sqrt(a.discriminant);
	a.coef = -a.b - a.discriminant;
	object->in = a.coef;
	object->out = a.coef + 2 * a.discriminant;
	if (a.coef < -DELTA)
		a.coef = object->out;
	return (a.coef);
}
