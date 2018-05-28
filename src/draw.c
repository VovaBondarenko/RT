#include "rt.h"

void	draw(t_env *env)
{
	int result;

	result = start_raytracing(env, env->cam);
	(result != 1) ? close_rt("ERROR: start_raytracing") : 0;
}
