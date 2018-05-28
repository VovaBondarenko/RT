#include "../../include/rt.h"

t_texture		generate_texture(t_env *e, int type, int width, int height)
{
	int			x;
	int			y;
	t_noise		noise;
	t_texture	texture;

	texture.width = width;
	texture.height = height;
	texture.define = 1;
	texture.normal_map = 0;
	noise = add_noise(e, width, height);
	add_func(&noise);
	if (!(texture.image = (t_color**)malloc(sizeof(t_color*) * height)))
		close_rt("ERROR: generate_texture");
	y = -1;
	while (++y < height)
	{
		x = -1;
		if (!(texture.image[y] = (t_color*)malloc(sizeof(t_color) * width)))
			close_rt("ERROR: texture image");
		while (++x < width)
			if (type < 3 && type > 0)
				texture.image[y][x] = noise.noise_func[type](&noise, x, y);
	}
	ft_memdel((void**)&noise.noise);
	return (texture);
}

int				obj_type(t_env *e, char *line)
{
	int		i;
	char	*type;

	i = -1;
	if (!(type = ft_strtrim(ft_strchr(line, ':') + 1)))
		close_rt("ERROR: obj_type");
	while (g_typeobj_str[++i].name != NULL)
	{
		if (ft_strcmp(type, g_typeobj_str[i].name) == 0)
		{
			ft_strdel(&type);
			return (g_typeobj_str[i].type);
		}
	}
	ft_strdel(&type);
	return (SPHERE);
}

double			*add_gr(t_color **image, int y, int x, t_texture texture)
{
	double	actual;
	double	*grad;

	grad = NULL;
	if ((grad = (double*)malloc(sizeof(double) * 4)) == NULL)
		return (NULL);
	actual = ft_intens(image[y][x]);
	grad[0] = (y - 1 > 0 ? ft_intens(image[y - 1][x]) : actual);
	grad[1] = (x - 1 > 0 ? ft_intens(image[y][x - 1]) : actual);
	grad[2] = (x + 1 < texture.width ? ft_intens(image[y][x + 1]) : actual);
	grad[3] = (y + 1 < texture.height ? ft_intens(image[y + 1][x]) : actual);
	return (grad);
}
