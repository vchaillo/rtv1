/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:23:02 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/06 21:36:14 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct				s_color
{
	int						r;
	int						g;
	int						b;
}							t_color;

typedef struct				s_vector
{
	float					x;
	float					y;
	float					z;
}							t_vector;

typedef struct				s_sphere
{
	t_vector				*pos;
	float					r;
}							t_sphere;

typedef struct				s_plane
{
	t_vector				*normal;
	float					offset;
}							t_plane;

typedef struct				s_object
{
	int						type;
	int						material;
	void					*object;
	t_color					*color;
	struct s_object			*next;
}							t_object;

typedef struct				s_hitpoint
{
	t_vector				*pos;
	t_vector				*normal;
	t_color					*color;
	t_object				*object;
}							t_hitpoint;

typedef struct				s_ray
{
	t_vector				*o;
	t_vector				*d;
	float					t;
	t_hitpoint				hitpoint;
}							t_ray;

typedef struct				s_light
{
	int						type;
	float					intensity;
	t_vector				*pos;
	t_vector				*dir;
	t_color					*color;
	struct s_light			*next;
}							t_light;

typedef struct				s_camera
{
	t_vector				*pos;
	float					ratio;
	float					fov;
	float					focale;
}							t_camera;

typedef struct				s_scene
{
	t_color					*background_color;
	t_camera				*camera;
	t_object				*objects;
	t_light					*lights;
	int						amb;
	int						dir;
	int						spot;
}							t_scene;

typedef struct				s_env
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*data;
	int						size;
	int						endian;
	int						bpp;
	t_scene					*scene;
	double					nb_rays;
}							t_env;

#endif
