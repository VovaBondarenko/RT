#include "../include/rt.h"

void	init_raytracing_param(t_env *env, t_cam *cam, double x, double y)
{
	env->scene.reflect.depth = 0;
	env->scene.refract.depth = 0;
	cam->ray.pos = cam->pos;
	cam->ray.dir = cam->origin;
	cam->ray.hit = create_vec3(0, 0, 0);
	cam->ray.dir = vec3_add(cam->origin,
		vec3_sub(
			vec3_fmult(create_vec3(1, 0, 0), cam->xaa * x),
			vec3_fmult(create_vec3(0, 1, 0), cam->yaa * y)));
	vec3_rotate(&cam->ray.dir, cam->dir);
	vec3_normalize(&cam->ray.dir);
}

int		start_raytracing(t_env *env, t_cam *cam)
{
	init_cam_param(env, cam);
	cam->y = -1;
	while (++(cam->y) < env->height)
	{
		cam->x = -1;
		while (++(cam->x) < env->width)
			super_sample(env, cam);
	}
	mlx_put_image_to_window(env->mlx->mlx,
		env->mlx->win, env->mlx->image.image, 0, 0);
	mlx_put_image_to_window(env->mlx->mlx,
		env->mlx->win, env->mlx->image.image, 0, 0);
	return (1);
}

t_vec3	get_point_color(t_env *env, t_cam *cam, t_ray ray)
{
	t_vec3	color;
	double	min;
	t_obj	*obj;

	min = INFINITY;
	color = create_vec3(0, 0, 0);
	obj = get_intersect(env, &ray, &min, env->obj);
	if (obj != NULL && min != INFINITY)
	{
		ray.hit = vec3_add(ray.pos, vec3_fmult(ray.dir, min));
		set_normal(env, &ray, obj);
		color = vec3_add(color, get_color(env, &ray, cam, obj));
		if (obj->material.reflect > 0 && obj->material.glossy == 0)
			color = vec3_add(color, reflect(env, ray, cam, obj));
		if (obj->material.reflect > 0 && obj->material.glossy > 0)
			color = vec3_add(color, reflect_glossy(env, ray, cam, obj));
		if (obj->material.transparency > 0)
			color = vec3_add(color, refract(env, ray, cam, obj));
	}
	return (color);
}
