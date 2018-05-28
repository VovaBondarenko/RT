#include "../include/rt.h"

void	init_intersection(t_env *env)
{
	env->intersect[SPHERE] = sphere;
	env->intersect[CONE] = cone;
	env->intersect[PLANE] = plane;
	env->intersect[CYLINDER] = cylinder;
	env->intersect[HYPERBOLOID] = hyperboloid;
	env->intersect[PARABOLOID] = paraboloid;
	env->intersect[TORUS] = torus;
	env->intersect[CHEWINGGUM] = chewing_gum;
	env->intersect[MOEBIUS] = mobius;
	env->intersect[DISC] = disc;
	env->intersect[SELLE] = selle;
	env->intersect[CUBE_HOLE] = cube_hole;
}

void	change_ray(t_ray *tmp_ray, t_obj *obj)
{
	tmp_ray->pos = vec3_sub(tmp_ray->pos, obj->pos);
	vec3_inverse_rotate(&tmp_ray->pos, obj->rotation);
	vec3_inverse_rotate(&tmp_ray->dir, obj->rotation);
}

void	save_obj(t_obj **out, t_obj *obj, double *tmin, double t)
{
	*out = obj;
	*tmin = t;
	(*out)->t = t;
}

t_obj	*get_intersect(t_env *e, t_ray *ray, double *tmin, t_obj *obj)
{
	t_obj	*out;
	double	t;
	t_ray	tray;

	out = NULL;
	while (obj != NULL)
	{
		tray = *ray;
		change_ray(&tray, obj);
		t = compute_intersect(e, &tray, obj);
		if (t > DELTA && t < *tmin)
			save_obj(&out, obj, tmin, t);
		obj = obj->next;
	}
	return (out);
}

void	set_normal(t_env *e, t_ray *ray, t_obj *obj)
{
	t_vec3	tr;

	tr = vec3_sub(ray->hit, obj->pos);
	vec3_inverse_rotate(&tr, obj->rotation);
	obj->norm = e->normal[obj->type](&tr, obj);
	if (obj->material.normal_p)
		obj->norm = create_vec3(obj->norm.x + sin(ray->hit.x),
	obj->norm.y, obj->norm.z);
	vec3_rotate(&obj->norm, obj->rotation);
	vec3_normalize(&obj->norm);
	obj->material.texture.norm = obj->norm;
}
