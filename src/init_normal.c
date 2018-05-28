#include "../include/rt.h"

void	init_normal(t_env *env)
{
	env->normal[SPHERE] = sphere_n;
	env->normal[CONE] = cone_n;
	env->normal[PLANE] = plane_n;
	env->normal[CYLINDER] = cylinder_n;
	env->normal[HYPERBOLOID] = hyperboloid_n;
	env->normal[PARABOLOID] = paraboloid_n;
	env->normal[TORUS] = torus_n;
	env->normal[CHEWINGGUM] = chewing_gum_n;
	env->normal[MOEBIUS] = moebius_n;
	env->normal[SELLE] = selle_n;
	env->normal[DISC] = plane_n;
	env->normal[CUBE_HOLE] = cube_hole_n;
}

double	compute_intersect(t_env *e, t_ray *tray, t_obj *obj)
{
	return (e->intersect[obj->type](tray, obj));
}
