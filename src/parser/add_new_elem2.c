#include "../../include/rt.h"

t_color	auto_texture1(t_noise *n, int x, int y)
{
	double	f;
	t_color	color;

	f = 2 - sqrt(fabs(sin(2 * PI * noise(n, x, y))));
	color.x = (1.0 * (1 - f) + 0.5 * f) * 255;
	color.y = (1.0 * (1 - f) + 0.6 * f) * 255;
	color.z = (1.0 * (1 - f) + 0.7 * f) * 255;
	return (color);
}

t_color	auto_texture2(t_noise *n, int x, int y)
{
	double	f;
	double	value;
	t_color	color;
	t_vec3	c1;
	t_vec3	c2;

	c1 = create_vec3(1.0, 0.5, 0.1);
	c2 = create_vec3(0.6, 0.10, 0.0);
	value = fmod(noise(n, x, y), 0.4);
	if (value > 0.2 / 2)
		value = 0.2 - value;
	f = (1 - cos(PI * value / (0.2 / 2))) / 2;
	color.x = (c1.x * (1 - f) + c2.x * f) * 255;
	color.y = (c1.x * (1 - f) + c2.y * f) * 255;
	color.z = (c1.z * (1 - f) + c2.z * f) * 255;
	return (color);
}

void	add_func(t_noise *n)
{
	n->noise_func[0] = NULL;
	n->noise_func[1] = auto_texture1;
	n->noise_func[2] = auto_texture2;
}
