#ifndef EXTRA_FUNCTION_H
# define EXTRA_FUNCTION_H

# include <math.h>
# define PI 3.1415926
# define DEG2RAD PI / 180
# define RAD2DEG 180 / PI
# define ABS(x) (x < 0 ? -x : x)

enum {X, Y, Z};

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_vec3i
{
	int				x;
	int				y;
	int				z;
}					t_vec3i;

typedef struct		s_vec2i
{
	int				x;
	int				y;
}					t_vec2i;

typedef struct		s_color
{
	unsigned char	x;
	unsigned char	y;
	unsigned char	z;
}					t_color;

t_vec3				create_vec3(double x, double y, double z);
t_vec3				vec3_add(t_vec3 vector1, t_vec3 vector2);
t_vec3				vec3_sub(t_vec3 vector1, t_vec3 vector2);
t_vec3				vec3_mult(t_vec3 vector1, t_vec3 vector2);
t_vec3				vec3_fmult(t_vec3 vector1, double arg);
double				vec3_dot(t_vec3 vector1, t_vec3 vector2);
t_vec3				vec3_norm(t_vec3 vector);
t_vec3i				vec3_convert(t_vec3 vec3);
void				vec3_normalize(t_vec3 *vector);
t_vec3				vec3_scale(t_vec3 vector, double scale);
t_vec3				vec3_cross(t_vec3 vector1, t_vec3 vector2);
void				vec3_rot(t_vec3 *vector, int xyz, double alfa);
int					vec3_rotate(t_vec3 *vector, t_vec3 vec3_rotate);
int					vec3_inverse_rotate(t_vec3 *vector, t_vec3 vec3_rotate);
t_vec3i				create_vec3i(int x, int y, int z);
t_vec2				create_vec2(double x, double y);
t_vec2i				create_vec2i(int x, int y);
t_color				vec3_to_color(t_vec3 vector);
t_vec3				color_to_vec3(t_color color);
t_vec3				vec3_reflect(t_vec3 vector, t_vec3 norm);
int					vec3_is_zero(t_vec3 vector);
double				ft_clampf(double value, double min, double max);
int					ft_clamp(int value, int min, int max);
int					ft_atoi_base(char *str, int base);
int					vec3_hex(const t_vec3 vec);
t_vec3				hex_vec3(const int hex);
double				ft_atof(const char *str);
double				power(double nb, int expo);
int					strdel(char **as);
void				vec3_clamp(t_vec3 *vector, double min, double max);

#endif
