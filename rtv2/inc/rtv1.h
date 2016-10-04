/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:22:57 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 20:58:14 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
*******************************************************************************
*/

/*
** basics defines
*/
# define TRUE 1
# define FALSE 0
# define ACTIVE 1
# define INACTIVE 0

/*
** errors defines
*/
# define MALLOC_ERROR 0
# define MLX_ERROR 1

/*
** window and camera defines
*/
# define WIN_W 1080
# define WIN_H 720
# define RATIO (float)WIN_W / (float)WIN_H
# define FOV tan((20 * 3.14) / 180)
# define FOCALE -1
# define EPSILON 0.01


/*
** objects defines
*/
# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3

/*
** lights defines
*/
# define AMB 0
# define SPOT 1
# define DIR 2

/*
*******************************************************************************
*/

/*
** 				mlx.c functions
*/
void			start_mlx(t_env *e);
int				mouse_hook(int button, int x, int y, t_env *e);
int				key_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);
void			fill_pixel(t_env *e, t_color *color, int x, int y);
/*
** 				init.c functions
*/
void			init_all(t_env *e);
void			init_objects(t_scene *scene);
void			init_lights(t_scene *scene);
/*
** 				draw.c functions
*/
void			erase_image(t_env *e);
void			draw(t_env *e);
/*
** 				raytracer.c functions
*/
int				get_ray_intersection(t_object *objects, t_ray *ray);
t_vector		*get_ray_dir(t_camera *camera, int x, int y);
t_color			*raytracer(t_scene *scene, int x, int y);
/*
** 				plane.c functions
*/
float			hit_plane(t_plane *plane, t_ray *ray);
/*
** 				sphere.c functions
*/
float			hit_sphere(t_sphere *sphere, t_ray *ray);
/*
** 				vector.c functions
*/
t_vector		*normalize(t_vector *vector);
t_vector		*vector_scalar(float scalar, t_vector *v);
t_vector		*vector_add(t_vector *v1, t_vector *v2);
t_vector		*vector_sub(t_vector *v1, t_vector *v2);
float			dot_product(t_vector *v1, t_vector *v2);
/*
** 				color.c functions
*/
t_color			*limit_color(t_color *color);
t_color			*scalar_color(float scalar, t_color *color);
t_color			*add_color(t_color *color1, t_color *color2);
t_color			*mult_color(t_color *color1, t_color *color2);
/*
** 				error.c functions
*/
void			print_error(int error_code);

/*
*******************************************************************************
*/

/*
** 				t_color.c functions
*/
t_color			*new_color(int color);
void			delete_color(t_color *color);
/*
** 				t_vector.c functions
*/
t_vector		*new_vector(float x, float y, float z);
void			delete_vector(t_vector *vector);
/*
** 				t_scene.c functions
*/
t_scene			*new_scene(t_color *background_color, t_camera *camera);
void			delete_scene(t_scene *scene);
/*
** 				t_camera.c functions
*/
t_camera		*new_camera(float x, float y, float z);
void			delete_camera(t_camera *camera);
/*
** 				t_sphere.c functions
*/
t_sphere		*new_sphere(float x, float y, float z, float r);
void			delete_sphere(t_sphere *sphere);
/*
** 				t_plane.c functions
*/
t_plane			*new_plane(float x, float y, float z, float d);
void			delete_plane(t_plane *plane);
/*
** 				t_object.c functions
*/
t_object		*new_object(int type, void *object, t_color *color);
void			add_object(t_scene *scene, t_object *new);
void			delete_objects(t_object *objects);
void			display_objects(t_scene *scene);
/*
** 				t_light.c functions
*/
t_light			*new_light(int type, float intensity, t_vector *pos,
							t_vector *dir, t_color *color);
void			add_light(t_scene *scene, t_light *new);
void			delete_lights(t_light *lights);
void			display_lights(t_scene *scene);

#endif
