#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "colors.h"
# include "structs.h"
# include "keycodes.h"

// basics defines
# define TRUE 1
# define FALSE 0

// window and camera defines
# define WIN_W 800
# define WIN_H 600
# define RATIO (float)WIN_W / (float)WIN_H
# define FOV tan((20 * 3.14) / 180)
# define FOCALE 1

// objects defines
# define SPHERE 0
# define PLAN 1

// lights defines
# define AMB 0
# define SPOT 1
# define DIR 2

// mlx.c functions
void			   start_mlx(t_env *e);
int				   mouse_hook(int button, int x, int y, t_env *e);
int				   key_hook(int keycode, t_env *e);
int				   expose_hook(t_env *e);
void			   fill_pixel(t_env *e, t_color color, int x, int y);
// init.c functions
void			   init_all(t_env *e);
void			   init_test_scene(t_env *e);
// draw.c functions
void			   erase_image(t_env *e);
void			   draw(t_env *e);
// raytracer.c functions
t_color			 raytracer(t_env *e, int x, int y);
t_vector	   get_ray_dir(t_env *e, int x, int y);
int 			   get_ray_intersection(t_env *e, t_ray *ray);
t_point      get_hitpoint_pos(t_ray *ray, float t);
// vector.c functions
t_vector	   normalize(t_vector vector);
t_vector	   vector_add(t_vector v1, t_vector v2);
float        dot_product(t_vector v1, t_vector v2);
// sphere.c functions
float			   solve_deg2(double a, double b, double c);
float        hit_sphere(t_env *e, t_ray *ray);
// plan.c functions
float        hit_plan(t_env *e, t_ray *ray);
// light.c functions
t_color      illuminate(t_env *e, t_ray *ray);
t_color      ambient(t_light amb);
t_color      spot(t_env *e, t_light spot, t_hitpoint hitpoint);
// color.c functions
t_color      scalar_color(float scalar, t_color color);
t_color      add_color(t_color color1, t_color color2);
t_color      mult_color(t_color color1, t_color color2);
t_color      new_color(int color);

#endif
