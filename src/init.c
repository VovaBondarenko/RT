#include "../include/rt.h"

int		valid_file_format(char *file_name)
{
	char *format;

	format = ft_strrchr(file_name, '.');
	if (format == NULL)
		return (0);
	if (ft_strcmp(format, ".yml") != 0)
		return (0);
	return (1);
}

void	init_file(t_env *env, char *file)
{
	if (valid_file_format(file))
		env->file_arg.file = file;
	else
		close_rt("Not falid file format. Need use yml");
	if ((env->file_arg.fd = open(file, O_RDWR)) == -1)
		close_rt("File can not open");
}

void	init_mlx_param(t_env *env)
{
	t_mlx *mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	(mlx == NULL) ? close_rt("Cant init mlx") : 0;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx, env->width, env->height, "RT");
	env->mlx = mlx;
	mlx->image.image = mlx_new_image(mlx, env->width, env->height);
	mlx->image.str = mlx_get_data_addr(mlx->image.image, &mlx->image.bpp,
		&mlx->image.size_len, &mlx->image.endian);
}

void	init_default_scene_param(t_env *env)
{
	env->scene.percent = 0;
	env->scene.loading_image = 0;
	env->scene.resync = 0;
	env->scene.sample = 0;
	env->scene.velocity = 0.6;
	env->scene.reflect.max = 1;
	env->scene.refract.max = 1;
}

void	init_default_param(t_env *env)
{
	env->width = DEFAULT_WIDTH;
	env->height = DEFAULT_HEIGHT;
	init_mlx_param(env);
	env->count_cam = 0;
	env->count_obj = 0;
	env->count_light = 0;
	init_default_scene_param(env);
}
