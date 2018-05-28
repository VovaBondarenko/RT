#include "../include/rt.h"

void	init_cam_param(t_env *env, t_cam *cam)
{
	double	w;
	double	h;
	double	coeff;

	env->scene.index = 32;
	cam->aa.increment = 1.0 / cam->aa.super_sample;
	cam->aa.coef = 1.0 / powf(cam->aa.super_sample, 2);
	coeff = (env->width < env->height ? env->width : env->height);
	w = env->width / coeff;
	h = env->height / coeff;
	cam->dist = 1.0 / tan(cam->fov / 2.0 * DEG2RAD);
	cam->origin = vec3_sub(vec3_add(create_vec3(0, 0, 0),
				vec3_add(vec3_fmult(create_vec3(0, 0, 1), cam->dist),
				vec3_fmult(create_vec3(0, 1, 0), h / 2.0))),
				vec3_fmult(create_vec3(1, 0, 0), w / 2.0));
	cam->xaa = w / (double)env->width;
	cam->yaa = h / (double)env->height;
}
