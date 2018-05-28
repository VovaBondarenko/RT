#include "../include/rt.h"

void	close_rt(char *str)
{
	ft_putendl(str);
	exit(0);
}

void	display_argc(void)
{
	close_rt("usage: ./RT scene/scene_name");
}

int		main(int argc, char *argv[])
{
	t_env env;

	(argc < 2) ? display_argc() : 0;
	(argc == 2) ? init_file(&env, argv[1]) : display_argc();
	init_default_param(&env);
	init_intersection(&env);
	init_normal(&env);
	parse_scene(&env);
	draw(&env);
	init_hook(&env);
	close_rt("Close RT SUCCESS");
	return (0);
}
