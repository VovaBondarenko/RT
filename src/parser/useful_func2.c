#include "../../include/rt.h"

t_vec3	*increase_size(t_env *e, t_vec3 *original, int *size)
{
	t_vec3	*new;
	int		increment;

	increment = 1000;
	*size = *size + increment;
	if (!(new = (t_vec3*)malloc(sizeof(*new) * (*size))))
		close_rt("ERROR");
	ft_memcpy(new, original, sizeof(*original) * (*size - increment));
	free(original);
	return (new);
}

int		check_objs(t_obj *obj)
{
	int		i;

	i = 0;
	if (obj == NULL)
		return (0);
	while (obj)
	{
		i++;
		obj = obj->next;
	}
	return (i);
}

double	ft_intens(t_color color)
{
	double		m;
	t_vec3		tmp;

	tmp = color_to_vec3(color);
	m = (tmp.x + tmp.y + tmp.z) / 3.0;
	return (m);
}

t_line	*load_buffer_elem(t_parse *buffer, int i)
{
	if (i == 0)
		return (buffer->cam);
	else if (i == 1)
		return (buffer->lgt);
	else if (i == 2)
		return (buffer->obj);
	else
		return (buffer->scene);
}
