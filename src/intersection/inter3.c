#include "../../include/rt.h"

int		inside(t_obj *m, t_vec3 h)
{
	double t;
	double s;

	t = atan2(h.y, h.x);
	if (inside_check(sin(t / 2)) != 0)
		s = h.z / sin(t / 2);
	else
		s = inside_check(cos(t)) ? (h.x / cos(t) - m->scale) / cos(t / 2) :
			(h.y / sin(t) - m->scale) / cos(t / 2);
	h.x -= (m->scale + s * cos(t / 2)) * cos(t);
	h.y -= (m->scale + s * cos(t / 2)) * sin(t);
	h.z -= s * sin(t / 2);
	if (inside_check(h.x * h.x + h.y * h.y + h.z * h.z))
		return (0);
	return (s >= -m->max && s <= m->max);
}

double	choose_mobi_root(double *roots, int ret, t_ray *ray, t_obj *obj)
{
	int			i;
	t_vec3		hit;

	i = 0;
	while (i < ret)
	{
		if (roots[i] > DELTA)
		{
			hit = vec3_add(vec3_fmult(ray->dir, roots[i]), ray->pos);
			if (inside(obj, hit))
				return (roots[i]);
		}
		i++;
	}
	return (INFINITY);
}

void	init_coeffs(t_mobius_coef m, double *coeff)
{
	coeff[3] = m.c * m.c * m.e + m.e * m.e * m.e - 2 * m.c * m.c * m.g - 2 * m.e
		* m.e * m.g + m.e * m.g * m.g;
	coeff[0] = (m.b * m.b * m.d + m.d * m.d * m.d - 2 * m.b * m.b * m.f - 2 *
		m.d * m.d * m.f
		+ m.d * m.f * m.f - 2 * m.b * m.f * m.a - m.d * m.a * m.a) / coeff[3];
	coeff[1] = (m.e * m.b * m.b - 2 * m.g * m.b * m.b + 2 * m.c * m.b * m.d + 3
		* m.e * m.d
		* m.d - 2 * m.g * m.d * m.d - 4 * m.c * m.b * m.f - 4 * m.e * m.d * m.f
		+ 2 * m.g * m.d
		* m.f + m.e * m.f * m.f - 2 * m.g * m.b * m.a - 2 * m.c * m.f * m.a -
		m.e * m.a * m.a) / coeff[3];
	coeff[2] = (2 * m.c * m.e * m.b - 4 * m.c * m.g * m.b + m.c * m.c * m.d + 3
		* m.e * m.e
		* m.d - 4 * m.e * m.g * m.d + m.g * m.g * m.d - 2 * m.c * m.c * m.f -
		2 * m.e * m.e * m.f
		+ 2 * m.e * m.g * m.f - 2 * m.c * m.g * m.a) / coeff[3];
}

double	mobius(t_ray *ray, t_obj *obj)
{
	double			a[4];
	double			root[3];
	t_mobius_coef	mobius;
	t_vec3			vector;
	int				ret;

	vector = ray->pos;
	mobius.a = obj->scale;
	mobius.b = vector.x;
	mobius.c = ray->dir.x;
	mobius.d = vector.y;
	mobius.e = ray->dir.y;
	mobius.f = vector.z;
	mobius.g = ray->dir.z;
	init_coeffs(mobius, a);
	ret = math_cub(a, root);
	return (choose_mobi_root(root, ret, ray, obj));
}

double	disc(t_ray *ray, t_obj *object)
{
	double				tmp;
	t_calculation_coef	a;

	if ((a.coef = plane(ray, object)) == INFINITY)
		return (INFINITY);
	ray->hit = vec3_add(ray->pos, vec3_fmult(ray->dir, a.coef));
	tmp = ray->hit.x * ray->hit.x + ray->hit.y * ray->hit.y +
	ray->hit.z * ray->hit.z;
	if (tmp > object->scale)
		return (INFINITY);
	return (a.coef);
}
