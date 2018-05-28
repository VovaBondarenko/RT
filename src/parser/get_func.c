#include "../../include/rt.h"

int			get_tt(char *line)
{
	if (ft_strstr(line, "NONE"))
		return (NONE);
	else if (ft_strstr(line, "MARBLE"))
		return (MARBLE);
	else if (ft_strstr(line, "WOOD"))
		return (WOOD);
	else if (ft_strstr(line, "CHECKER"))
		return (CHECKER);
	else
		return (BMP);
}

char		*get_tn(t_env *e, char *line)
{
	char	*name;
	char	*del;

	if (!(name = ft_strdup(ft_strchr(line, ':') + 1)))
		close_rt("ERROR");
	del = name;
	if (!(name = ft_strtrim(name)))
		close_rt("ERROR");
	ft_strdel(&del);
	return (name);
}

char		*get_line(t_env *e, int fd, t_line *first)
{
	char	*line;
	t_line	*prev;
	t_line	*cur;

	cur = first;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(*line))
			return (line);
		if (is_new_block(line))
			return (line);
		if (!comment_line(line))
		{
			prev = cur;
			cur->next = init_list(e, line, prev);
			cur = cur->next;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (NULL);
}

int			what_light(char *line)
{
	if (ft_strstr(line, "DIRECTIONAL"))
		return (DIRECTIONAL);
	else if (ft_strstr(line, "SPOT"))
		return (SPOT);
	return (POINT);
}

t_color		check_gr(double *grad, t_obj *obj)
{
	t_vec3		color;
	double		diffx;
	double		diffy;
	double		scale;

	scale = obj->material.texture.normal_s;
	diffx = grad[1] - grad[2];
	diffy = grad[0] - grad[3];
	color.x = vec3_norm(create_vec3(1, diffx * scale, 0)).y;
	color.y = vec3_norm(create_vec3(1, diffy * scale, 0)).y;
	color.z = sqrt(1 - ft_clampf(color.x * color.x + color.y * color.y, 0, 1));
	vec3_normalize(&color);
	return (vec3_to_color(vec3_add(vec3_fmult(color, 0.5),
		create_vec3(0.5, 0.5, 0.5))));
}
