#include "../../include/rt.h"

#define MATTEXT obj->material.texture.norm
#define MATTRANS obj->material.transparency

void			refract_dir(t_env *e, t_ray *ray, t_obj *obj)
{
	float	n;
	float	calc[3];
	t_vec3	norm;

	ray->pos = ray->hit;
	norm = obj->material.texture.normal_map ? MATTEXT : obj->norm;
	calc[0] = vec3_dot(norm, ray->dir);
	if (calc[0] > 0.0)
	{
		e->scene.refract.normal1 = obj->material.refract;
		e->scene.refract.normal2 = 1.0;
		norm = vec3_fmult(norm, -1.0);
	}
	else
	{
		e->scene.refract.normal1 = 1.0;
		e->scene.refract.normal2 = obj->material.refract;
		calc[0] = -calc[0];
	}
	n = e->scene.refract.normal1 / e->scene.refract.normal2;
	calc[2] = n * n * (1.0 - calc[0] * calc[0]);
	calc[1] = sqrt(1.0 - calc[2]);
	ray->dir = vec3_add(vec3_fmult(ray->dir, n),
	vec3_fmult(norm, (n * calc[0] - calc[1])));
	vec3_normalize(&ray->dir);
}

t_vec3			refract(t_env *env, t_ray ray, t_cam *cam, t_obj *obj)
{
	t_vec3	color;
	t_vec3	tex_color;

	color = create_vec3(0, 0, 0);
	if (obj->material.texture.transparency_map)
	{
		tex_color = texture_map(obj, obj->material.texture.image, ray.hit);
		MATTRANS = (tex_color.x + tex_color.y + tex_color.z) / 3.0;
	}
	if (env->scene.refract.depth < env->scene.refract.max)
	{
		env->scene.refract.depth++;
		refract_dir(env, &ray, obj);
		color = vec3_add(color, vec3_fmult(get_point_color(env, cam, ray),
			(float)obj->material.transparency));
		if (obj->material.absorp < 1.0)
			color = vec3_fmult(color, powf(obj->material.absorp, obj->scale));
	}
	return (color);
}

t_vec3			reflect(t_env *env, t_ray ray, t_cam *cam, t_obj *obj)
{
	t_vec3	color;

	color = create_vec3(0, 0, 0);
	if (env->scene.reflect.depth < env->scene.reflect.max)
	{
		env->scene.reflect.depth++;
		ray.pos = ray.hit;
		if (obj->material.texture.normal_map)
			ray.dir = vec3_reflect(ray.dir, obj->material.texture.norm);
		else
			ray.dir = vec3_reflect(ray.dir, obj->norm);
		color = vec3_add(color, get_point_color(env, cam, ray));
		color = vec3_fmult(color, obj->material.reflect);
	}
	return (color);
}

static t_vec3	glossy_reflection_direction(t_ray ray, t_obj *obj)
{
	t_vec3	cone;
	t_vec3	tmp;
	float	kg;

	kg = obj->material.glossy;
	tmp.x = rand() / (float)RAND_MAX * kg - (kg * 0.5);
	tmp.y = rand() / (float)RAND_MAX * kg - (kg * 0.5);
	tmp.z = rand() / (float)RAND_MAX * kg - (kg * 0.5);
	cone = vec3_add(vec3_add(ray.pos, ray.dir), tmp);
	return (vec3_norm(vec3_sub(cone, ray.pos)));
}

t_vec3			reflect_glossy(t_env *env, t_ray ray, t_cam *cam, t_obj *obj)
{
	t_vec3	color;
	t_vec3	dir;
	int		i;

	color = (t_vec3) {0, 0, 0};
	if (env->scene.reflect.depth < env->scene.reflect.max)
	{
		env->scene.reflect.depth++;
		ray.pos = ray.hit;
		if (obj->material.texture.normal_map)
			ray.dir = vec3_reflect(ray.dir, obj->material.texture.norm);
		else
			ray.dir = vec3_reflect(ray.dir, obj->norm);
		dir = ray.dir;
		i = -1;
		while (++i < env->scene.sample)
		{
			ray.dir = glossy_reflection_direction(ray, obj);
			color = vec3_add(color, get_point_color(env, cam, ray));
			ray.dir = dir;
		}
		color = vec3_fmult(color, 1.0 / (float)env->scene.sample);
		color = vec3_fmult(color, obj->material.reflect);
	}
	return (color);
}
