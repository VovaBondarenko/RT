#include "../../include/extra_function.h"
#include <libft.h>

int		strdel(char **as)
{
	if (as != NULL)
	{
		free(*as);
		*as = NULL;
	}
	return (1);
}
