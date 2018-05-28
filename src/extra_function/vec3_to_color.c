#include "../../include/extra_function.h"

t_color	vec3_to_color(t_vec3 vector)
{
	t_color color;

	color.x = (unsigned char)(vector.x * 255);
	color.y = (unsigned char)(vector.y * 255);
	color.z = (unsigned char)(vector.z * 255);
	return (color);
}
