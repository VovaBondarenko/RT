#include "../../include/rt.h"

int		is_new_block(char *line)
{
	return (ft_strncmp(line, "cameras:", 8) == 0 ||
			ft_strncmp(line, "lights:", 7) == 0 ||
			ft_strncmp(line, "objects:", 8) == 0 ||
			ft_strncmp(line, "scenes:", 6) == 0 ||
			ft_strncmp(line, "...", 3) == 0);
}

void	my_awesome_parser(t_env *e)
{
	t_parse		buffer;

	if ((e->file_arg.fd = open(e->file_arg.file, O_RDWR)) == -1)
		close_rt("ERROR: open file");
	buffer.scene = init_list(e, "scene", NULL);
	buffer.cam = init_list(e, "cameras", NULL);
	buffer.lgt = init_list(e, "lights", NULL);
	buffer.obj = init_list(e, "objects", NULL);
	fill_buffer(e, e->file_arg.fd, &buffer);
	if (close(e->file_arg.fd) == -1)
		close_rt("ERROR: close file");
	fill_scene(e, &buffer);
}

void	parse_scene(t_env *env)
{
	my_awesome_parser(env);
}
