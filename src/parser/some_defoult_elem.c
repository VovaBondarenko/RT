#include "../../include/rt.h"

t_material		default_material(void)
{
	t_material	material;

	material.color = create_vec3(1, 1, 1);
	material.reflect = 0;
	material.refract = 0;
	material.ambient_occlusion = 0.1;
	material.diffuse = 0.1;
	material.specular = 1.0;
	material.transparency = 0;
	material.absorp = 0;
	material.shine = 256;
	material.glossy = 0;
	material.texture.type = NONE;
	material.texture.define = 0;
	material.texture.transparency_map = 0;
	material.texture.rotation = 0;
	material.texture.normal_s = 1;
	material.shadow = 1;
	material.fresnel.define = 0;
	material.texture.scale = 1;
	return (material);
}

void			default_object(t_obj *object)
{
	object->type = SPHERE;
	object->pos = create_vec3(0, 0, 0);
	object->dir = create_vec3(0, 1, 0);
	object->cut_figure = create_vec3(0, 0, 0);
	object->rotation = create_vec3(0, 0, 0);
	object->prev = NULL;
	object->next = NULL;
	object->torus_radius1 = 1;
	object->torus_radius2 = 2;
	object->scale = 1;
	object->min = -INFINITY;
	object->max = INFINITY;
	object->material = default_material();
}

void			default_light(t_light *light)
{
	light->light_type = POINT;
	light->scale = 0.12;
	light->pos = create_vec3(0, 0, 0);
	light->dir = create_vec3(0, 0, 1);
	light->color = create_vec3(1, 1, 1);
	light->light_intensive = 1;
	light->attenuation = 0.05;
	light->light_alfa = 75;
	light->light_outer = 2;
	light->shadow_coef = 0.7;
	light->shadow_type = HARD;
}

void			default_cam(t_env *e, t_cam *cam)
{
	if (cam != NULL)
	{
		cam->type = DEFAULT;
		cam->pos = create_vec3(0, 0, 0);
		cam->dir = create_vec3(0, 0, 1);
		cam->image = new_img(e);
		cam->filter.invert = 0;
		cam->filter.scale = 0;
		cam->filter.gamma = 1.0;
		cam->index = 0;
		cam->fov = 60;
		cam->selected_obj = NULL;
		cam->win = NULL;
		cam->aa.super_sample = 1;
	}
}
