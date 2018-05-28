#include "../../include/rt.h"
#include <stdio.h>
void	fill_object_(t_env *e, t_line *line, t_obj *new)
{
	if (ft_strstr(line->line, "scale:"))
		new->scale = range_value(line->line, 0.01, 1000);
	else if (ft_strstr(line->line, "min:"))
		new->min = range_value(line->line, -INFINITY, INFINITY);
	else if (ft_strstr(line->line, "max:"))
		new->max = range_value(line->line, -INFINITY, INFINITY);
	else if (ft_strstr(line->line, "tor_r1:"))
		new->torus_radius1 = range_value(line->line, 0, INFINITY);
	else if (ft_strstr(line->line, "tor_r2:"))
		new->torus_radius2 = range_value(line->line, 0, INFINITY);
	else if (ft_strstr(line->line, "material:"))
		add_material(e, &new->material, line);
}

int		fill_object(t_env *e, t_line *line, t_obj *new)
{
	if (ft_strstr(line->line, "type:"))
		new->type = obj_type(e, line->line);
	else if (ft_strstr(line->line, "pos:"))
		new->pos = range_vector(e, line->line);
	else if (ft_strstr(line->line, "rot:"))
		new->rotation = range_vector(e, ft_strchr(line->line, ':'));
	else if (ft_strstr(line->line, "dir:"))
		new->dir = vec3_norm(range_vector(e, line->line));
	else if (ft_strstr(line->line, "cut:"))
		new->cut_figure = range_vector(e, line->line);
	else
		fill_object_(e, line, new);
	return (1);
}

void	fill_scene(t_env *e, t_parse *buffer)
{
	add_scene(e, buffer->scene);
	e->cam = add_camera(e, buffer->cam);
	e->light = add_light(e, buffer->lgt);
	e->obj = add_object(e, buffer->obj);
	del_buffer(buffer);
	if (!e->count_cam)
		close_rt("ERROR: fill scene");
}

t_line	*init_list(t_env *e, char *line, t_line *prev)
{
	t_line *cur;

	if (!(cur = (t_line*)malloc(sizeof(t_line))))
		close_rt("ERROR: init list");
	cur->line = ft_strdup(line);
	cur->next = NULL;
	cur->prev = prev;
	return (cur);
}

void	fill_buffer(t_env *e, const int fd, t_parse *buffer)
{
	char		*tmp;
	char		*line;

	while (get_next_line(fd, &line) > 0 && ft_strcmp(line, "...") != 0)
	{
		tmp = ft_strdup(line);
		if (ft_strncmp(tmp, "scene:", 6) == 0 && strdel(&tmp))
			tmp = get_line(e, fd, buffer->scene);
		if (ft_strncmp(tmp, "cameras:", 8) == 0 && strdel(&tmp))
			tmp = get_line(e, fd, buffer->cam);
		if (ft_strncmp(tmp, "lights:", 7) == 0 && strdel(&tmp))
			tmp = get_line(e, fd, buffer->lgt);
		if (ft_strncmp(tmp, "objects:", 8) == 0 && strdel(&tmp))
			tmp = get_line(e, fd, buffer->obj);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
