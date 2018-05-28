#include "../../include/rt.h"

t_vec3	random_sample(t_ray ray, float scale, t_vec3 hit)
{
	t_vec3 tmp;
	t_vec3 dir;

	tmp.x = rand() / (float)RAND_MAX * scale - (scale * 0.5);
	tmp.y = rand() / (float)RAND_MAX * scale - (scale * 0.5);
	tmp.z = rand() / (float)RAND_MAX * scale - (scale * 0.5);
	dir = vec3_sub(hit, vec3_add(ray.pos, tmp));
	return (vec3_norm(dir));
}

void	shadow_hard(t_env *env, t_vec3 *color, t_light light, t_obj *obj)
{
	double min;

	min = INFINITY;
	light.ray.dir = vec3_norm(vec3_sub(light.ray.pos, light.pos));
	light.ray.pos = light.pos;
	if (get_intersect(env, &light.ray, &min, env->obj) != obj)
		*color = vec3_fmult(*color, 1.0 - light.shadow_coef);
}

void	shadow_soft(t_env *env, t_vec3 *color, t_light light, t_obj *obj)
{
	int		index;
	int		shadow;
	t_vec3	hit;
	t_vec3	dir;
	double	min;

	index = 0;
	shadow = 1;
	hit = light.ray.pos;
	light.ray.dir = vec3_norm(vec3_sub(hit, light.pos));
	light.ray.pos = light.pos;
	dir = light.ray.dir;
	while (index < env->scene.sample)
	{
		light.ray.dir = random_sample(light.ray, light.scale, hit);
		min = INFINITY;
		if (get_intersect(env, &light.ray, &min, env->obj) != obj)
			shadow++;
		light.ray.dir = dir;
		index++;
	}
	*color = vec3_fmult(*color, 1.0 - ((float)shadow /
		(float)env->scene.sample * light.shadow_coef));
}

void	get_shadow(t_env *env, t_vec3 *color, t_light light, t_obj *obj)
{
	light.shadow_type == HARD ? shadow_hard(env, color, light, obj) : 0;
	light.shadow_type == SOFT ? shadow_soft(env, color, light, obj) : 0;
}
