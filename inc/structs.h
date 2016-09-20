/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 21:23:00 by vchaillo          #+#    #+#             */
/*   Updated: 2016/05/19 21:58:08 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_camera
{
	float			    x;
	float		      y;
	float			    z;
}				        t_camera;

typedef struct	s_screen
{
	float		  	  iar;
	float			    fov;
	float			    d;
}					      t_screen;

typedef struct  s_vector
{
	float         vx;
	float         vy;
	float         vz;
}				        t_vector;

typedef struct	s_sphere
{
  float			    x;
  float			    y;
  float			    z;
  float			    r;
  int				    color;
}			        	t_sphere;

typedef struct	s_plan
{
  float			    a;
  float			    b;
	float			    c;
  float			    d;
  int				    color;
}			        	t_plan;

typedef struct	s_ray
{
	t_camera     	o;
	t_vector     	d;
	float		      t;
}				        t_ray;

typedef struct	s_env
{
  void		      *mlx;
  void		      *win;
  void		      *img;
  char		      *data;
  int			      size;
  int			      endian;
  int           bpp;
  t_camera      camera;
  t_screen      screen;
	t_sphere	    sphere;
  t_plan		    plan;
  int			      background;
  double        nb_rays;
}				        t_env;

#endif
