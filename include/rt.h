#ifndef RT_H
# define RT_H

# include <libft.h>
# include "extra_function.h"
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# define DEFAULT_WIDTH 600
# define DEFAULT_HEIGHT 600
# define TEXTURE_DEFAULT_WIDTH 2560
# define TEXTURE_DEFAULT_HEIGHT 1440
# define DELTA 1e-9
# define ERROR -1;
# define SUCCESS 1;
# define DEFAULT_CAM_X
# define DEFAULT_CAM_Y
# define DEFAULT_CAM_Z

enum {DEFAULT};

enum { SPHERE, CONE, PLANE, CYLINDER, DISC,
	HYPERBOLOID, PARABOLOID, CHEWINGGUM, TORUS,
	MOEBIUS, CUBE_HOLE, SELLE };

enum { POINT, SPOT, DIRECTIONAL };

enum { NONE, MARBLE, WOOD, BMP, CHECKER };

enum { HARD, SOFT };

typedef struct		s_math_cube
{
	double			q;
	double			r;
	double			bq;
	double			br;
	double			bq3;
	double			br2;
	double			cr2;
	double			cq3;
	double			sqrtbq;
	double			sgnbr;
	double			ba;
	double			bb;
	double			r1;
	double			r2;
	double			r3;
	double			norm;
	int				index;
	double			alfa;
	double			ratio;
}					t_math_cube;

typedef struct		s_math_quadro
{
	double			u[3];
	double			v[3];
	double			zarr[4];
	double			args[3];
	double			aa;
	double			pp;
	double			qq;
	double			rr;
	double			rc;
	double			sc;
	double			tc;
	double			mt;
	double			w1r;
	double			w1i;
	double			w2r;
	double			w2i;
	double			w3r;
	double			v1;
	double			v2;
	double			arg;
	double			theta;
	double			disc;
	double			h;
	double			qcub;
	double			rcub;
	double			bq;
	double			br;
	double			bq3;
	double			br2;
	double			cr2;
	double			cq3;
	double			sqrtbq;
	double			sqrtbq3;
	double			sgnbr;
	double			modbr;
	double			norm;
	double			sqrt_disc;
	double			ba;
	double			bb;
	double			mod_diffbabb;
	int				k1;
	int				k2;
}					t_math_quadro;

typedef struct		s_type_obj_str
{
	int				type;
	char			*name;
}					t_type_obj_str;

typedef struct		s_refract
{
	int				depth;
	int				max;
	double			normal1;
	double			normal2;
	int				refraction_index;
}					t_refract;

typedef struct		s_reflect
{
	int				depth;
	int				max;
}					t_reflect;

typedef struct		s_ray
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			hit;
	double			index;
}					t_ray;

typedef struct		s_file_info
{
	char			*file;
	int				fd;
}					t_file_info;

typedef struct		s_scene
{
	int				percent;
	int				loading_image;
	int				resync;
	int				sample;
	double			velocity;
	t_refract		refract;
	t_reflect		reflect;
	int				index;
}					t_scene;

typedef struct		s_image
{
	void			*image;
	char			*str;
	int				size_len;
	int				bpp;
	int				endian;
}					t_image;

typedef struct		s_line
{
	char			*line;
	struct s_line	*next;
	struct s_line	*prev;
}					t_line;

typedef struct		s_parse
{
	t_line			*scene;
	t_line			*cam;
	t_line			*obj;
	t_line			*lgt;
}					t_parse;

typedef struct		s_noise
{
	double			*noise;
	int				w_max;
	int				h_max;
	int				len;
	int				pas;
	int				octave;
	t_color			(*noise_func[3])(struct s_noise*, int, int);
}					t_noise;

typedef struct		s_coef_fresnel
{
	double			refract_coef;
	double			reflect_coef;
	char			define;
}					t_coef_fresnel;

typedef struct		s_bi_filter
{
	int				x;
	int				y;
	double			ur;
	double			vr;
	double			uo;
	double			vo;
	t_vec3			c[4];
}					t_bi_filter;

typedef struct		s_filter
{
	char			scale;
	char			invert;
	double			gamma;
}					t_filter;

typedef struct		s_anti_aliasing
{
	int				super_sample;
	double			coef;
	double			increment;
}					t_anti_aliasing;

typedef struct		s_mobius_coef
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		f;
	double		g;
}					t_mobius_coef;

typedef struct		s_texture
{
	t_color			**image;
	t_color			**bmp;
	t_vec3			norm;
	int				length;
	int				width;
	int				height;
	int				bpp;
	int				type;
	int				filter;
	int				define;
	int				transparency_map;
	int				normal_map;
	double			scale;
	double			normal_s;
	double			rotation;
	char			*name;
}					t_texture;

typedef struct		s_material
{
	t_texture		texture;
	double			ambient_occlusion;
	double			diffuse;
	double			reflect;
	double			refract;
	double			glossy;
	double			specular;
	double			shine;
	double			transparency;
	double			absorp;
	int				shadow;
	int				normal_p;
	t_coef_fresnel	fresnel;
	t_vec3			color;
}					t_material;

typedef struct		s_obj
{
	int				type;
	t_vec3			cut_figure;
	t_vec3			rotation;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			norm;
	double			tan_alfa;
	t_material		material;
	double			scale;
	double			scale2;
	double			min;
	double			max;
	double			torus_radius1;
	double			torus_radius2;
	double			t;
	unsigned int	index;
	double			dist;
	double			in;
	double			out;
	struct s_obj	*prev;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_calculation_coef
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			discriminant;
	double			coef;
	t_vec3			length;
}					t_calculation_coef;

typedef struct		s_cam
{
	int				x;
	int				y;
	int				xx;
	int				yy;
	double			aa_x;
	double			aa_y;
	char			type;
	double			dist;
	double			fov;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			origin;
	t_ray			ray;
	struct s_image	image;
	t_filter		filter;
	struct s_cam	*next;
	struct s_cam	*prev;
	struct s_cam	*win;
	t_anti_aliasing	aa;
	struct s_obj	*obj;
	int				index;
	double			xaa;
	double			yaa;
	struct s_obj	*selected_obj;
}					t_cam;

typedef struct		s_light
{
	int				index;
	t_vec3			pos;
	t_vec3			dir;
	struct s_ray	ray;
	int				shadow_type;
	int				light_type;
	double			shadow_coef;
	double			scale;
	double			attenuation;
	double			intensive;
	t_vec3			color;
	double			light_alfa;
	double			light_outer;
	double			light_intensive;
	struct s_light	*next;
}					t_light;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	struct s_image	image;
	t_filter		filter;

}					t_mlx;

typedef struct		s_env
{
	t_mlx			*mlx;
	t_file_info		file_arg;
	int				width;
	int				height;
	t_scene			scene;
	t_cam			*cam;
	int				count_cam;
	t_obj			*obj;
	t_light			*light;
	int				count_obj;
	int				count_light;
	t_vec3			color;
	double			(*intersect[13])(t_ray *, t_obj *);
	t_vec3			(*normal[13])(t_vec3 *, t_obj *);
}					t_env;

void				init_intersection(t_env *env);
void				init_normal(t_env *env);
void				init_default_scene_param(t_env *env);
void				init_cam_param(t_env *env, t_cam *cam);
void				close_rt(char *str);
void				init_file(t_env *env, char *file);
void				init_default_param(t_env *env);
double				*add_gr(t_color **img, int y, int x, t_texture text);
int					obj_type(t_env *e, char *line);
t_texture			generate_texture(t_env *e, int type, int width, int height);
t_obj				*div_bbox(t_obj *original_box, t_env *e);
void				my_awesome_parser(t_env *e);
int					is_new_block(char *line);
t_cam				*create_cam(t_env *e, t_line *cam_line, t_cam *prev);
t_image				new_img(t_env *e);
t_light				*create_light(t_env *e, t_line *light_line);
void				arg_light(t_line *line, t_light *new);
t_obj				*new_object(t_env *e, t_line *object_line);
void				fill_buffer(t_env *e, int fd, t_parse *buffer);
t_line				*init_list(t_env *e, char *line, t_line *prev);
void				fill_scene(t_env *e, t_parse *buffer);
void				fill_object_(t_env *e, t_line *line, t_obj *new);
int					fill_object(t_env *e, t_line *line, t_obj *new);
int					what_light(char *line);
t_color				check_gr(double *grad, t_obj *obj);
char				*get_tn(t_env *e, char *line);
char				*get_line(t_env *e, int fd, t_line *first);
void				del_buffer(t_parse *buffer);
int					get_tt(char *line);
int					comment_line(char *line);
int					next_(char *line, int i);
t_vec3				ft_pap(t_vec3 *vect, int pos, int max, char sign);
t_vec3				get_point(char *line, t_obj *parent);
t_vec3				*increase_size(t_env *e, t_vec3 *original, int *size);
int					check_objs(t_obj *obj);
double				ft_intens(t_color color);
void				csg_count(t_env *e, t_line **line);
t_vec3				range_vector(t_env *e, char *line);
t_line				*load_buffer_elem(t_parse *buffer, int i);
double				range_value(char *line, double min, double max);
short				is_true(char *line);
t_vec3				convert_color(char *line);
int					check_csg(t_line *line);
void				add_scene(t_env *e, t_line *scene);
t_cam				*add_camera(t_env *e, t_line *cam_line);
t_obj				*add_bbox(t_obj *objs, t_env *e);
t_obj				*add_csg_obj(t_env *e, t_line *object_line);
void				add_cube_(t_obj *cube, double k);
void				add_cube(t_env *e, t_obj *cube);
void				add_nm(t_env *e, t_obj *obj);
t_obj				*add_object(t_env *e, t_line *object_line);
t_light				*add_light(t_env *e, t_line *light_line);
t_noise				add_noise(t_env *e, int w, int h);
void				add_texture(t_env *e, t_material *mat, char *line);
void				add_material(t_env *e, t_material *mat, t_line *line);
void				add_material_(t_env *e, t_material *mat, char *line);
t_obj				*add_p(t_env *e, int fd, t_obj *parent);
t_obj				*add_obj(char *file, t_env *e, t_obj *parent);
void				add_fr(t_obj *obj);
t_color				add_marble(t_noise *n, int x, int y);
void				dd_func(t_noise *noise);
t_color				add_wood(t_noise *n, int x, int y);
void				add_fs(t_env *e, t_obj *csg, t_line *line);
void				add_op(t_env *e, t_obj *csg, char *line);
void				add_csg(t_env *e, t_obj *csg, t_line *line);
t_obj				*add_triangle(char *line, t_vec3 *vect,
										t_obj *parent, int max);
t_obj				*new_triangle(t_vec3 p1, t_vec3 p2, t_vec3 p3,
										t_obj *parent);
t_material			default_material(void);
void				default_object(t_obj *object);
void				default_light(t_light *light);
void				default_cam(t_env *e, t_cam *cam);
void				parse_scene(t_env *env);
double				cone_check(t_ray *ray, t_obj *object, t_vec3 vector);
double				cone(t_ray *ray, t_obj *object);
double				sphere(t_ray *ray, t_obj *object);
double				cube_hole(t_ray *ray, t_obj *object);
double				chewing_gum(t_ray *ray, t_obj *object);
double				cylinder(t_ray *ray, t_obj *object);
double				plane(t_ray *ray, t_obj *object);
int					inside(t_obj *m, t_vec3 h);
double				choose_mobi_root(double *roots, int ret,
											t_ray *ray, t_obj *obj);
void				init_coeffs(t_mobius_coef m, double *coeff);
double				mobius(t_ray *ray, t_obj *obj);
double				disc(t_ray *ray, t_obj *object);
double				paraboloid(t_ray *ray, t_obj *obj);
double				hyperboloid(t_ray *ray, t_obj *obj);
void				another_math_shit(double *r, double *zarr);
void				compute_coeffs(t_ray *ray, t_obj *object, double *coef);
double				torus(t_ray *ray, t_obj *obj);
double				cut_selle(t_ray *ray, t_obj *obj, double tmp);
double				selle(t_ray *ray, t_obj *obj);
t_vec3				plane_n(t_vec3 *vector, t_obj *obj);
t_vec3				cone_n(t_vec3 *vector, t_obj *obj);
t_vec3				cylinder_n(t_vec3 *vector, t_obj *obj);
t_vec3				sphere_n(t_vec3 *vector, t_obj *obj);
t_vec3				torus_n(t_vec3 *vector, t_obj *obj);
t_vec3				selle_n(t_vec3 *vector, t_obj *obj);
t_vec3				paraboloid_n(t_vec3 *vector, t_obj *obj);
t_vec3				moebius_n(t_vec3 *vector, t_obj *obj);
t_vec3				hyperboloid_n(t_vec3 *vector, t_obj *obj);
t_vec3				cube_hole_n(t_vec3 *vector, t_obj *obj);
t_vec3				chewing_gum_n(t_vec3 *vector, t_obj *obj);
int					math_cub(double *a, double *r);
int					cub_3(t_math_cube cub, double *a, double *r);
int					cub_2(t_math_cube cub, double *a, double *r);
int					cub_(t_math_cube cub, double *a, double *r);
int					solve_linear(double a, double b, double *r);
void				fill_roots(double *a, double d, double *r);
int					solve_quadratic(double *a, double *r);
t_math_cube			math_coef(double *a);
void				init_stru(t_math_quadro *q, double *a);
void				math_position(t_math_quadro *q);
void				math_negative(t_math_quadro *q);
int					math_shit(t_math_quadro *q, double *a, double *r);
int					solve_quartic(double *a, double *r);
double				root(double *r, int n);
void				draw(t_env *env);
void				super_sample(t_env *env, t_cam *cam);
int					start_raytracing(t_env *env, t_cam *cam);
int					start_progressive_raytracing(t_env *env, t_cam *cam);
void				init_raytracing_param(t_env *env,
											t_cam *cam, double x, double y);
t_vec3				get_point_color(t_env *env, t_cam *cam, t_ray ray);
void				invert_filter(t_vec3 *color);
void				scale_filter(t_vec3 *color);
void				gamma_color(double gamma, t_vec3 *color);
void				put_image(t_image *image, int x, int y, t_vec3 color);
t_obj				*get_intersect(t_env *env, t_ray *ray,
									double *min, t_obj *obj);
void				set_normal(t_env *e, t_ray *ray, t_obj *obj);
void				get_shadow(t_env *e, t_vec3 *color,
								t_light light, t_obj *obj);
t_vec3				get_color(t_env *env, t_ray *ray, t_cam *cam, t_obj *obj);
void				pull_vec(double *u, double u0, double u1, double u2);
t_vec3				reflect(t_env *env, t_ray ray, t_cam *cam, t_obj *obj);
t_vec3				reflect_glossy(t_env *env, t_ray ray,
											t_cam *cam, t_obj *obj);
t_vec3				refract(t_env *env, t_ray ray, t_cam *cam, t_obj *obj);
int					inside_check(double number);
double				get_fresnel(t_vec3 v, t_vec3 n, double dir);
void				set_fresnel(t_obj *obj);
t_vec3				bump_normal(t_obj *obj, t_ray *ray);
t_vec3				texture_map(t_obj *object, t_color **img, t_vec3 vector);
t_vec3				b_filter(t_obj *object, t_color **img, double u, double v);
t_vec3				plane_tm(t_obj *object, t_color **img, t_vec3 vactor);
t_vec3				sphere_tm(t_obj *obj, t_color **img, t_vec3 vactor);
t_vec3				cylinder_tm(t_obj *object, t_color **img, t_vec3 vactor);
void				arg_cam(t_env *e, t_line *line, t_cam *new);
int					swapd(double *a, double *b);
int					undone_opp(double *a, double *r);
void				cubic_run(t_math_quadro *q);
void				add_func(t_noise *n);
void				display(t_env *e, int u, int v);
void				init_hook(t_env *env);
double				noise(t_noise *n, double x, double y);
double				new_noise(t_noise *n, double x, double y);
double				get_value(t_noise *n, int i, int j);
double				interpolate(double a, double b, double x);
t_noise				init_noise_structure(t_env *e, int w, int h);
double				compute_intersect(t_env *e, t_ray *tray, t_obj *obj);

extern	t_type_obj_str		g_typeobj_str[13];

#endif
