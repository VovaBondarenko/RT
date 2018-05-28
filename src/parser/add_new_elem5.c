#include "../../include/rt.h"

t_cam	*add_camera(t_env *e, t_line *cam_line)
{
	t_line	*line;
	t_cam	*tmp;
	t_cam	*camera;
	t_cam	*current;

	line = cam_line;
	if (!(current = (t_cam*)malloc(sizeof(t_cam))))
		close_rt("ERROR: add camera");
	current->next = NULL;
	camera = current;
	while (line != NULL)
	{
		if (ft_strstr(line->line, "- camera:"))
		{
			current->next = create_cam(e, line->next, current);
			current = current->next;
			camera->next->prev = current;
			current->next = camera->next;
		}
		line = line->next;
	}
	tmp = camera;
	camera = camera->next;
	ft_memdel((void**)&tmp);
	return (camera);
}

void	add_scene(t_env *e, t_line *scene)
{
	t_line *line;

	line = scene;
	while (line != NULL)
	{
		if (ft_strstr(line->line, "recursion_reflect:"))
			e->scene.reflect.max = range_value(line->line, 0, 16);
		else if (ft_strstr(line->line, "refract:"))
			e->scene.refract.max = range_value(line->line, 0, 16);
		else if (ft_strstr(line->line, "velocity:"))
			e->scene.velocity = range_value(line->line, 0, 100);
		else if (ft_strstr(line->line, "sampling:"))
			e->scene.sample = range_value(line->line, 0, 4096);
		line = line->next;
	}
}
