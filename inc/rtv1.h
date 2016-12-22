/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:22:57 by vchaillo          #+#    #+#             */
/*   Updated: 2016/12/19 16:37:27 by valentinchaillou89###   ########.fr       */
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
# include "macros.h"

/*
** 				main functions
*/
void			init_all(t_env *e);
void			init_objects(t_scene *scene);
void			init_lights(t_scene *scene);
void			print_error(int error_code);
/*
** 				core functions
*/
void			get_hitpoint(t_object *object, t_ray *ray, float t_min);
int				get_ray_intersection(t_object *objects, t_ray *ray);
t_vector		get_ray_dir(t_camera *camera, int x, int y);
t_color			raytracer(t_env *e, int x, int y);
float			hit_plane(t_plane *plane, t_ray *ray);
float			hit_sphere(t_sphere *sphere, t_ray *ray);
float			hit_cylinder(t_cylinder *cylinder, t_ray *ray);
float			hit_cone(t_cone *cone, t_ray *ray);
int				is_in_shadow(t_object *objects, t_ray *ray);
t_color			specular(t_ray *v_ray, t_light *spot, t_ray *l_ray);
t_color			diffuse(t_hitpoint hitpoint, t_light *spot, t_ray *ray);
t_color			phong(t_env *e, t_light *spot, t_ray *v_ray);
t_color			illuminate(t_env *e, t_ray *ray);
/*
** 				gui functions
*/
void			start_mlx(t_env *e);
int				expose_hook(t_env *e);
int				key_hook(int keycode, t_env *e);
int				mouse_hook(int button, int x, int y, t_env *e);
void			fill_pixel(t_env *e, t_color color, int x, int y);
void			erase_image(t_env *e);
void			draw(t_env *e);
/*
** 				tools functions
*/
float			solve_deg2(double a, double b, double c);
t_vector		normalize(t_vector vector);
t_vector		vector_scalar(float scalar, t_vector v);
t_vector		vector_add(t_vector v1, t_vector v2);
t_vector		vector_sub(t_vector v1, t_vector v2);
float			dot_product(t_vector v1, t_vector v2);
t_color			limit_color(t_color color);
t_color			average_color(t_color color);
t_color			scalar_color(float scalar, t_color color);
t_color			add_color(t_color color1, t_color color2);
t_color			mult_color(t_color color1, t_color color2);
/*
** 				structs functions
*/
t_color			new_color(int color);
t_vector		new_vector(float x, float y, float z);
t_scene			*new_scene(t_color background_color, t_camera *camera);
void			delete_scene(t_scene *scene);
t_camera		*new_camera(float x, float y, float z);
void			delete_camera(t_camera *camera);
t_sphere		*new_sphere(float x, float y, float z, float r);
void			delete_sphere(t_sphere *sphere);
t_plane			*new_plane(float x, float y, float z, float d);
void			delete_plane(t_plane *plane);
t_cylinder		*new_cylinder(t_vector axis, t_vector pos, float r);
void			delete_cylinder(t_cylinder *cylinder);
t_object		*new_object(int type, void *object, t_color color, int mat);
void			add_object(t_scene *scene, t_object *new);
void			delete_objects(t_object *objects);
t_light			*new_light(int type, float intensity, t_vector vector,
							t_color color);
void			add_light(t_scene *scene, t_light *new);
void			delete_lights(t_light *lights);

#endif
