#include "../../include/rt.h"

void	pixelate(t_env *env, t_cam *cam, t_vec3 color)
{
	int x;
	int y;

	x = 0;
	while (x < env->scene.index)
	{
		y = -1;
		while (++y < env->scene.index)
			put_image(&cam->image, cam->x + x, cam->y + y, color);
		x++;
	}
}

void	filtering(t_cam *cam, t_vec3 *color)
{
	cam->filter.invert ? invert_filter(color) : 0;
	cam->filter.scale ? scale_filter(color) : 0;
	gamma_color(cam->filter.gamma, color);
	vec3_clamp(color, 0, 1);
}

void	super_sample(t_env *e, t_cam *cam)
{
	double	sx;
	double	sy;
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	sx = (double)cam->x;
	while (sx < cam->x + 1.0)
	{
		sy = (double)cam->y;
		while (sy < cam->y + 1.0)
		{
			init_raytracing_param(e, cam, sx, sy);
			color = vec3_add(color, vec3_fmult(get_point_color(e, cam,
			cam->ray), cam->aa.coef));
			sy += cam->aa.increment;
		}
		sx += cam->aa.increment;
	}
	filtering(cam, &color);
	put_image(&e->mlx->image, cam->x, cam->y, color);
}
