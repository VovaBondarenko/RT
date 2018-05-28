#include "../../include/extra_function.h"

int		vec3_hex(const t_vec3 vec)
{
	int		hex;

	hex = (vec.z * 255);
	hex += (vec.y * 255) * 256;
	hex += (vec.x * 255) * 256 * 256;
	return (hex);
}
