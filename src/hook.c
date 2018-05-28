#include "../include/rt.h"

int		exit_hook(t_mlx *i)
{
	mlx_destroy_image(i->mlx, i->image.image);
	mlx_destroy_window(i->mlx, i->win);
	close_rt("RT closed");
	exit(0);
	return (0);
}

int		press_check(int k, t_mlx *i)
{
	if (k == 53)
		exit_hook(i);
	return (0);
}

void	init_hook(t_env *env)
{
	env->mlx->filter = env->cam->filter;
	mlx_hook(env->mlx->win, 2, 0, press_check, env->mlx);
	mlx_hook(env->mlx->win, 17, 0, exit_hook, env->mlx);
	mlx_loop(env->mlx->mlx);
}
