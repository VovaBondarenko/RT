#include "../../include/rt.h"

void	add_nm(t_env *e, t_obj *obj)
{
	int		x;
	int		y;
	double	*grad;

	y = -1;
	grad = NULL;
	obj->material.texture.bmp =
	(t_color**)malloc(sizeof(t_color*) * obj->material.texture.height);
	obj->material.texture.bmp == NULL ? close_rt("ERROR: normalmap") : 0;
	while (++y < obj->material.texture.height)
	{
		x = -1;
		obj->material.texture.bmp[y] =
		(t_color*)malloc(sizeof(t_color) * obj->material.texture.width);
		obj->material.texture.bmp[y] == NULL ? close_rt("ERROR: normalmap") : 0;
		while (++x < obj->material.texture.width)
		{
			grad = add_gr(obj->material.texture.image, y, x,
				obj->material.texture);
			grad == NULL ? close_rt("ERROR: normalmap") : 0;
			obj->material.texture.bmp[y][x] = check_gr(grad, obj);
			ft_memdel((void**)&grad);
		}
	}
}

t_obj	*add_object(t_env *e, t_line *object_line)
{
	t_line	*line;
	t_obj	*tmp;
	t_obj	*object;
	t_obj	*current;

	line = object_line;
	if (!(current = (t_obj*)malloc(sizeof(t_obj))))
		close_rt("ERROR: new_object");
	current->next = NULL;
	object = current;
	while (line != NULL)
	{
		if (ft_strstr(line->line, "- object:"))
		{
			current->next = new_object(e, line->next);
			current = current->next;
		}
		line = line->next;
	}
	tmp = object;
	object = object->next;
	ft_memdel((void**)&tmp);
	return (object);
}

t_light	*add_light(t_env *e, t_line *light_line)
{
	t_line	*line;
	t_light	*tmp;
	t_light	*light;
	t_light	*current;

	line = light_line;
	if (!(current = (t_light*)malloc(sizeof(t_light))))
		close_rt("ERROR");
	current->next = NULL;
	light = current;
	while (line != NULL)
	{
		if (ft_strstr(line->line, "- light:"))
		{
			current->next = create_light(e, line->next);
			current = current->next;
		}
		line = line->next;
	}
	tmp = light;
	light = light->next;
	ft_memdel((void**)&tmp);
	return (light);
}
