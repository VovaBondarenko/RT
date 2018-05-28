#include "../../include/extra_function.h"

t_vec3	hex_vec3(const int hex)
{
	t_vec3	color;

	color.z = hex % 256 / 255.0;
	color.y = (hex >> 8) % 256 / 255.0;
	color.x = (hex >> 16) % 256 / 255.0;
	return (color);
}
