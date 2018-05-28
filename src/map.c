#include "../include/rt.h"

t_vec3	plane_tm(t_obj *object, t_color **img, t_vec3 vactor)
{
	double	u;
	double	v;
	t_vec3	u_axis;
	t_vec3	v_axis;

	u_axis = create_vec3(object->norm.y, object->norm.z, -object->norm.x);
	v_axis = vec3_cross(u_axis, object->norm);
	u = vec3_dot(vactor, u_axis) * object->material.texture.scale;
	v = vec3_dot(vactor, v_axis) * object->material.texture.scale;
	u = u - floor(u);
	v = v - floor(v);
	return (color_to_vec3(img[(int)(v * (object->material.texture.height - 1))]
				[(int)(u * (object->material.texture.width - 1))]));
}

t_vec3	sphere_tm(t_obj *obj, t_color **img, t_vec3 vactor)
{
	t_vec3	d;
	double	u;
	double	v;
	int		i;
	int		j;

	d = vec3_norm(vec3_sub(vactor, obj->pos));
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = 0.5 - asin(d.y) / M_PI;
	i = ft_clamp(u * obj->material.texture.width, 0,
		obj->material.texture.width - 1);
	j = ft_clamp(v * obj->material.texture.height, 0,
			obj->material.texture.height - 1);
	return (color_to_vec3(img[j][i]));
}

t_vec3	cylinder_tm(t_obj *object, t_color **img, t_vec3 vactor)
{
	t_vec3	d;
	double	u;
	double	v;
	int		i[2];

	d = vec3_sub(vactor, vec3_mult(object->pos, object->dir));
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = d.y / (object->max - object->min);
	v = v - floor(v);
	i[0] = ft_clamp(u * object->material.texture.width,
		0, object->material.texture.width - 1);
	i[1] = ft_clamp(v * object->material.texture.height,
		0, object->material.texture.height - 1);
	return (color_to_vec3(img[i[1]][i[0]]));
}

t_vec3	texture_map(t_obj *object, t_color **img, t_vec3 vector)
{
	if (!object->material.texture.define)
		return (object->material.color);
	if (object->type == PLANE)
		return (plane_tm(object, img, vector));
	else if (object->type == SPHERE)
		return (sphere_tm(object, img, vector));
	else if (object->type == CYLINDER || object->type == CONE)
		return (cylinder_tm(object, img, vector));
	return (object->material.color);
}
