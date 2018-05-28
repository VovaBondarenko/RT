#include "../../include/rt.h"

t_cam	*create_cam(t_env *e, t_line *cam_line, t_cam *prev)
{
	t_cam		*new;
	t_line		*line;

	line = cam_line;
	!(new = (t_cam*)malloc(sizeof(t_cam))) ? close_rt("ERROR: create_cam") : 0;
	default_cam(e, new);
	while (line != NULL && !ft_strstr(line->line, "- camera:"))
	{
		arg_cam(e, line, new);
		line = line->next;
	}
	e->count_cam++;
	new->prev = prev;
	new->next = NULL;
	return (new);
}
