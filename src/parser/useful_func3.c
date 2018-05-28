#include "../../include/rt.h"

void	del_buffer(t_parse *buffer)
{
	int			i;
	t_line		*del;
	t_line		*tmp;

	i = 0;
	while (i < 4)
	{
		del = load_buffer_elem(buffer, i);
		while (del != NULL)
		{
			tmp = del;
			ft_strdel(&del->line);
			ft_memdel((void**)&del);
			del = tmp->next;
		}
		i++;
	}
}

int		comment_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	if (line[i] == '#')
		return (1);
	else
		return (0);
}

t_vec3	ft_pap(t_vec3 *vect, int pos, int max, char sign)
{
	if (sign == '-')
		pos = max - pos + 1;
	if (pos <= max && pos >= 0)
		return (vect[pos]);
	else
		return ((t_vec3){0, 0, 0});
}

int		next_(char *line, int i)
{
	while (ft_isdigit(line[i]) || line[i] == '/' || line[i] == '-')
		i++;
	while (!ft_isdigit(line[i]) && line[i])
		i++;
	return (i);
}

t_vec3	get_point(char *line, t_obj *parent)
{
	int		i;
	t_vec3	result;

	i = 0;
	while ((!ft_isdigit(line[i]) && line[i] != '-') && line[i])
		i++;
	result.x = ft_atof(line + i) * parent->scale;
	while (ft_isdigit(line[i]) || line[i] == '.' || line[i] == ','
			|| line[i] == '-' || line[i] == 'E')
		i++;
	while ((!ft_isdigit(line[i]) && line[i] != '-') && line[i])
		i++;
	result.y = ft_atof(line + i) * parent->scale;
	while (ft_isdigit(line[i]) || line[i] == '.' || line[i] == ','
			|| line[i] == '-' || line[i] == 'E')
		i++;
	while ((!ft_isdigit(line[i]) && line[i] != '-')
			&& line[i])
		i++;
	result.z = ft_atof(line + i) * parent->scale;
	result = vec3_add(result, parent->pos);
	return (result);
}
