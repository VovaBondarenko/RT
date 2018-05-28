#include "../../include/rt.h"

t_noise		add_noise(t_env *e, int w, int h)
{
	int		i;
	int		poctave;
	t_noise	noise;

	i = -1;
	noise.octave = 7;
	noise.pas = 100;
	poctave = pow(2, noise.octave - 1);
	noise.w_max = (int)ceil(w * poctave / noise.pas);
	noise.h_max = (int)ceil(h * poctave / noise.pas);
	noise.len = noise.w_max * noise.h_max;
	if (!(noise.noise = (double*)malloc(sizeof(double) * noise.len)))
		close_rt("ERROR: noise");
	while (++i < noise.len)
		noise.noise[i] = ((double)rand()) / RAND_MAX;
	return (noise);
}

void		add_texture(t_env *e, t_material *material, char *line)
{
	material->texture.name = get_tn(e, line);
	material->texture.type = get_tt(material->texture.name);
	if (material->texture.type == NONE || material->texture.type == CHECKER)
		return ;
	else
		material->texture = generate_texture(e, material->texture.type,
			TEXTURE_DEFAULT_WIDTH, TEXTURE_DEFAULT_HEIGHT);
}

void		add_material_(t_env *e, t_material *material, char *line)
{
	if (ft_strstr(line, "refract:"))
		material->refract = range_value(line, 0, 10);
	else if (ft_strstr(line, "texture_transparency:"))
		material->texture.transparency_map = is_true(line);
	else if (ft_strstr(line, "absorbtion:"))
		material->absorp = range_value(line, 0, 1);
	else if (ft_strstr(line, "texture:"))
		add_texture(e, material, line);
	else if (ft_strstr(line, "receive_shadow:"))
		material->shadow = is_true(line);
	else if (ft_strstr(line, "transparency:"))
		material->transparency = range_value(line, 0, 1);
}

void		add_material(t_env *e, t_material *material, t_line *line)
{
	while (line != NULL && !ft_strstr(line->line, "- object:"))
	{
		if (ft_strstr(line->line, "color:"))
			material->color = convert_color(line->line);
		else if (ft_strstr(line->line, "ambient:"))
			material->ambient_occlusion = range_value(line->line, 0, 1);
		else if (ft_strstr(line->line, "diffuse:"))
			material->diffuse = range_value(line->line, 0, 10);
		else if (ft_strstr(line->line, "specular:"))
			material->specular = range_value(line->line, 0, 50);
		else if (ft_strstr(line->line, "shininess:"))
			material->shine = range_value(line->line, 0, 16384);
		else if (ft_strstr(line->line, "glossiness:"))
			material->glossy = range_value(line->line, 0, 2);
		else if (ft_strstr(line->line, "reflect:"))
			material->reflect = range_value(line->line, 0, 1);
		else
			add_material_(e, material, line->line);
		line = line->next;
	}
}

void		add_fr(t_obj *obj)
{
	obj->material.fresnel.reflect_coef = pow((obj->material.refract - 1.0) /
		(obj->material.refract + 1.0), 2);
	obj->material.fresnel.refract_coef = 1.0 -
		obj->material.fresnel.reflect_coef;
}
