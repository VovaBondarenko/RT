#include "../../include/rt.h"

void	another_math_shit(double *r, double *zarr)
{
	r[0] = zarr[0];
	r[1] = zarr[1];
	r[2] = zarr[2];
	r[3] = zarr[3];
}

void	compute_coeffs(t_ray *ray, t_obj *object, double *coef)
{
	t_vec3		x;
	double		a[4];

	x = ray->pos;
	a[0] = vec3_dot(ray->dir, ray->dir);
	a[1] = vec3_dot(x, x) - object->torus_radius2 - object->torus_radius1;
	a[2] = vec3_dot(x, ray->dir);
	a[3] = 4 * object->torus_radius2;
	coef[0] = (a[1] * a[1] - a[3] * (object->torus_radius1 - x.y * x.y))
	/ a[0] * a[0];
	coef[1] = (4 * a[2] * a[1] + 2 * a[3] * x.y * ray->dir.y) / a[0] * a[0];
	coef[2] = (2 * a[0] * a[1] + 4 * a[2] * a[2] + a[3] * ray->dir.y *
		ray->dir.y) / a[0] * a[0];
	coef[3] = (4 * a[0] * a[2]) / a[0] * a[0];
}

double	torus(t_ray *ray, t_obj *obj)
{
	double	a[4];
	double	roots[4];
	int		n;

	compute_coeffs(ray, obj, a);
	n = solve_quartic(a, roots);
	if (n == 0)
		return (INFINITY);
	if (n == 2)
	{
		if (roots[0] < 0)
			return (roots[1] < 0 ? INFINITY : roots[1]);
		else
			return (roots[0]);
	}
	n = 0;
	while (n < 4)
	{
		if (roots[n] > 0)
			return (roots[n]);
		n++;
	}
	return (INFINITY);
}

double	cut_selle(t_ray *ray, t_obj *obj, double tmp)
{
	t_vec3	vector;

	vector = vec3_add(ray->pos, vec3_fmult(ray->dir, tmp));
	if (vector.x > obj->max || vector.x < obj->min || vector.y > obj->max ||
		vector.y < obj->min || vector.z > obj->max || vector.z < obj->min)
	{
		vector = vec3_add(ray->pos, vec3_fmult(ray->dir, obj->out));
		if (vector.x > obj->max || vector.x < obj->min || vector.y > obj->max ||
			vector.y < obj->min || vector.z > obj->max || vector.z < obj->min)
			return (INFINITY);
		tmp = obj->out;
	}
	return (tmp);
}

double	selle(t_ray *ray, t_obj *obj)
{
	double	a[5];
	int		result;

	obj->in = INFINITY;
	obj->out = INFINITY;
	a[2] = ray->dir.x * ray->dir.x - ray->dir.z * ray->dir.z;
	a[1] = 2 * (ray->dir.x * ray->pos.x - ray->dir.z * ray->pos.z) +
		ray->dir.y;
	a[0] = ray->pos.x * ray->pos.x - ray->pos.z *
		ray->pos.z + ray->pos.y;
	if (!(result = solve_quadratic(a, &a[3])))
		return (INFINITY);
	obj->in = a[3];
	obj->out = a[4];
	if (obj->in < 0)
	{
		obj->in = obj->out;
		if (obj->in < 0)
			return (INFINITY);
	}
	return (cut_selle(ray, obj, obj->in));
}
