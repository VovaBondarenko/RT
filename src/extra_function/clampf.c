#include "../../include/extra_function.h"

double	ft_clampf(double value, double min, double max)
{
	value > max ? value = max : 0;
	value < min ? value = min : 0;
	return (value);
}

int		ft_clamp(int value, int min, int max)
{
	value > max ? value = max : 0;
	value < min ? value = min : 0;
	return (value);
}
