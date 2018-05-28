#include "../../include/rt.h"

#define NORM new->light_outer

t_obj		*new_object(t_env *e, t_line *object_line)
{
	t_obj		*new;
	t_line		*line;

	!(object_line) ? close_rt("ERROR: 0 objects") : 0;
	line = object_line;
	!(new = (t_obj*)malloc(sizeof(t_obj))) ? close_rt("ERROR: new object") : 0;
	default_object(new);
	while (line != NULL && !ft_strstr(line->line, "- object:") &&
		!ft_strchr(line->line, '(') && fill_object(e, line, new))
		line = line->next;
	e->count_obj++;
	new->index = e->count_obj;
	if (new->material.texture.normal_map && new->material.texture.define)
		add_nm(e, new);
	new->scale2 = new->scale * new->scale;
	new->torus_radius1 *= new->torus_radius1;
	new->torus_radius2 *= new->torus_radius2;
	new->tan_alfa = tan(new->scale) * tan(new->scale);
	new->material.fresnel.define ? add_fr(new) : 0;
	return (new);
}

void		arg_light(t_line *line, t_light *new)
{
	if (ft_strstr(line->line, "scale:"))
		new->scale = range_value(line->line, 0, 10);
	else if (ft_strstr(line->line, "shadow_intensity:"))
		new->shadow_coef = range_value(line->line, 0, 1);
	else if (ft_strstr(line->line, "shadow:"))
		new->shadow_type = ft_strstr(line->line, "SOFT") ? SOFT : HARD;
	else if (ft_strstr(line->line, "intensity:"))
		new->intensive = range_value(line->line, 0, 10);
	else if (ft_strstr(line->line, "attenuation:"))
		new->attenuation = range_value(line->line, 0.0000001, 10);
	else if (ft_strstr(line->line, "cutoff:"))
		new->light_alfa = range_value(line->line, 0, 360);
	else if (ft_strstr(line->line, "cutoff_outer:"))
		new->light_outer = range_value(line->line, 0, 180);
}

t_light		*create_light(t_env *e, t_line *light_line)
{
	t_light		*new;
	t_line		*line;

	line = light_line;
	!(new = (t_light*)malloc(sizeof(t_light))) ? close_rt("ERROR: new light")
		: 0;
	default_light(new);
	while (line != NULL && !ft_strstr(line->line, "- light:"))
	{
		if (ft_strstr(line->line, "type:"))
			new->light_type = what_light(line->line);
		else if (ft_strstr(line->line, "pos:"))
			new->pos = range_vector(e, line->line);
		else if (ft_strstr(line->line, "dir:"))
			new->dir = range_vector(e, line->line);
		else if (ft_strstr(line->line, "color:"))
			new->color = convert_color(line->line);
		arg_light(line, new);
		line = line->next;
	}
	e->count_light++;
	new->next = NULL;
	NORM = cos((new->light_alfa + new->light_outer) * 0.5 * DEG2RAD);
	new->light_alfa = cos(new->light_alfa * 0.5 * DEG2RAD);
	return (new);
}

t_image		new_img(t_env *e)
{
	t_image	img;

	if (!(img.image = mlx_new_image(e->mlx->mlx, e->width, e->height)))
		close_rt("ERROR: mlx_new_image");
	if (!(img.str = mlx_get_data_addr(img.image, &img.bpp, &img.size_len,
		&img.endian)))
		close_rt("ERROR: mlx_get_data_addr");
	return (img);
}

void		arg_cam(t_env *e, t_line *line, t_cam *new)
{
	if (ft_strstr(line->line, "pos:"))
		new->pos = range_vector(e, line->line);
	else if (ft_strstr(line->line, "dir:"))
		new->dir = range_vector(e, line->line);
	else if (ft_strstr(line->line, "fov:"))
		new->fov = range_value(line->line, 1, 180);
	else if (ft_strstr(line->line, "supersampling:"))
		new->aa.super_sample = range_value(line->line, 1, 16);
	else if (ft_strstr(line->line, "invert:"))
		new->filter.invert = range_value(line->line, 0, 1);
	else if (ft_strstr(line->line, "scale:"))
		new->filter.scale = range_value(line->line, 0, 1);
}
