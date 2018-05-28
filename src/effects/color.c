#include "../../include/rt.h"

void	set_color(t_obj *obj, t_ray *ray)
{
	double	d;

	d = 0.0;
	if (obj->material.texture.type == CHECKER)
	{
		d = fmod((floor(ray->hit.x * obj->material.texture.scale) +
		floor(ray->hit.z * obj->material.texture.scale)), 2.0) * 0.8;
		d = ABS(d);
		obj->material.color = create_vec3(d, d, d);
	}
	if (obj->material.texture.define)
	{
		obj->material.color =
		texture_map(obj, obj->material.texture.image, ray->hit);
	}
}

void	set_light(t_vec3 hit, t_obj *obj, t_light *light)
{
	double	alfa;
	double	delta;

	light->ray.pos = hit;
	if (light->light_type == DIRECTIONAL)
	{
		light->ray.dir = vec3_fmult(light->dir, -1);
		obj->dist = 1.0;
	}
	else
	{
		light->ray.dir = vec3_sub(light->pos, hit);
		obj->t = sqrt(light->ray.dir.x * light->ray.dir.x +
				light->ray.dir.y * light->ray.dir.y +
				light->ray.dir.z * light->ray.dir.z);
		obj->dist = (1.0 + obj->t * obj->t * light->attenuation);
	}
	if (light->light_type == SPOT)
	{
		alfa = vec3_dot(light->dir, vec3_norm(vec3_fmult(light->ray.dir, -1)));
		delta = light->light_alfa - light->light_outer;
		light->light_intensive = ft_clampf((alfa - light->light_outer) /
			delta, 0, 1);
	}
	vec3_normalize(&light->ray.dir);
}

t_vec3	get_specular(t_obj *obj, t_cam *cam, t_light *light)
{
	t_vec3	dir;
	double	alfa;
	double	result;

	dir = vec3_norm(vec3_sub(light->ray.dir, cam->ray.dir));
	alfa = ft_clampf(vec3_dot(obj->material.texture.norm, dir), 0, 1);
	result = pow(alfa, obj->material.shine);
	result = result * obj->material.specular * light->intensive / obj->dist;
	light->light_type == SPOT ? result *= light->light_intensive : 0;
	return (vec3_fmult(light->color, result));
}

t_vec3	get_diffuse(t_obj *obj, t_light *light)
{
	double	alfa;
	double	result;

	alfa = ft_clampf(vec3_dot(light->ray.dir, obj->material.texture.norm),
	0, 1);
	result = obj->material.diffuse * light->intensive * alfa / obj->dist;
	light->light_type == SPOT ? result *= light->light_intensive : 0;
	return (vec3_fmult(light->color, result));
}

t_vec3	get_color(t_env *env, t_ray *ray, t_cam *cam, t_obj *obj)
{
	t_light	*light;
	t_vec3	color;
	t_vec3	specular;
	t_vec3	diffuse;

	color = create_vec3(0, 0, 0);
	light = env->light;
	while (light != NULL)
	{
		set_light(ray->hit, obj, light);
		set_color(obj, ray);
		color = vec3_add(color,
			vec3_fmult(light->color, obj->material.ambient_occlusion));
		diffuse = get_diffuse(obj, light);
		specular = get_specular(obj, cam, light);
		color = vec3_add(color, vec3_add(diffuse, specular));
		color = vec3_mult(color, obj->material.color);
		obj->material.shadow ? get_shadow(env, &color, *light, obj) : 0;
		light = light->next;
	}
	return (color);
}
