#include "../../include/rt.h"

t_noise	init_noise_structure(t_env *e, int w, int h)
{
	int		i;
	int		poctave;
	t_noise	noise;

	i = -1;
	noise.octave = 7;
	noise.pas = 100;
	poctave = pow(2, noise.octave - 1);
	noise.w_max = (int)ceil(w * poctave / noise.pas);
	noise.h_max = (int)ceil(h * poctave / noise.pas);
	noise.len = noise.w_max * noise.h_max;
	if (!(noise.noise = (double*)malloc(sizeof(double) * noise.len)))
		close_rt("Crash");
	while (++i < noise.len)
		noise.noise[i] = ((double)rand()) / RAND_MAX;
	return (noise);
}

double	interpolate(double a, double b, double x)
{
	return (a * (1 - x) + b * x);
}

double	get_value(t_noise *n, int i, int j)
{
	return (n->noise[(i % n->w_max) + (j % n->h_max) * n->w_max]);
}

double	new_noise(t_noise *n, double x, double y)
{
	int		i;
	int		j;
	double	ya[2];
	double	xpas;
	double	ypas;

	xpas = x / n->pas;
	ypas = y / n->pas;
	i = (int)(xpas);
	j = (int)(ypas);
	ya[0] = interpolate(get_value(n, i, j), get_value(n, i + 1, j),
					fmod(xpas, 1));
	ya[1] = interpolate(get_value(n, i, j + 1), get_value(n, i + 1, j + 1),
					fmod(xpas, 1));
	return (interpolate(ya[0], ya[1], fmod(ypas, 1)));
}

double	noise(t_noise *n, double x, double y)
{
	int		i[2];
	double	j[2];

	i[0] = -1;
	i[1] = 1;
	j[0] = 1.0;
	j[1] = 0.0;
	while (++i[0] < n->octave)
	{
		j[1] += j[0] * new_noise(n, x * i[1], y * i[1]);
		j[0] *= 0.6;
		i[1] *= 2;
	}
	return (j[1] * (1 - 0.6) / (1 - j[0]));
}
