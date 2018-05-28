#include "../../include/extra_function.h"
#include <libft.h>

int		is_blank(char c)
{
	return ((c == ' ' || c == '\n' || c == '\v' ||
			c == '\t' || c == '\r' || c == '\f'));
}

double	ft_atof(const char *str)
{
	int		sign;
	double	i;
	double	value;
	int		exponent;

	i = 1;
	sign = 0;
	value = 0;
	while (is_blank(*str))
		str++;
	*str == '-' ? sign = 1 : 0;
	*str == '-' || *str == '+' ? str++ : 0;
	while ('0' <= *str && *str <= '9')
		value = value * 10 + (*str++ - '0');
	if (*str == '.' && (str++))
		while ('0' <= *str && *str <= '9')
			value += (*str++ - '0') / (i *= 10);
	if (*str == 'E' && (str++))
	{
		exponent = ft_atoi(str);
		if (exponent != 0)
			value = value * power(10, exponent);
	}
	return (sign == 1 && value > 0 ? -value : value);
}
