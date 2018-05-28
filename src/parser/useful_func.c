#include "../../include/rt.h"

t_vec3		range_vector(t_env *e, char *line)
{
	int		i;
	char	**tab;
	t_vec3	vec;

	i = -1;
	vec = (t_vec3) {0, 0, 0};
	if (!(tab = ft_strsplit(line, ',')))
		close_rt("ERROR");
	while (tab[++i] != NULL)
	{
		if (ft_strstr(tab[i], "x:"))
			vec.x = range_value(tab[i], -1000, 1000);
		else if (ft_strstr(tab[i], "y:"))
			vec.y = range_value(tab[i], -1000, 1000);
		else if (ft_strstr(tab[i], "z:"))
			vec.z = range_value(tab[i], -1000, 1000);
		ft_strdel(&tab[i]);
	}
	free(tab);
	tab = NULL;
	return (vec);
}

double		range_value(char *line, double min, double max)
{
	int			i;
	double		value;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	(line[i - 1] == '-') ? i -= 1 : 0;
	value = ft_atof(&line[i]);
	value = ft_clampf(value, min, max);
	return (value);
}

short		is_true(char *line)
{
	if (ft_strstr(line, "true") ||
		ft_strstr(line, "TRUE") ||
		ft_strstr(line, "True"))
		return (1);
	else
		return (0);
}

t_vec3		convert_color(char *line)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	while (*line != '#' && ft_strncmp(line, "0x", 2) != 0)
		line++;
	color = hex_vec3(ft_atoi_base(line, 16));
	return (color);
}
