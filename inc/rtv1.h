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

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "colors.h"
# include "structs.h"

# define WIN_W 800
# define WIN_H 600

// mlx.c functions
void			start_mlx(t_env *e);
int				mouse_hook(int button, int x, int y, t_env *e);
int				key_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);

// init.c functions
void			init_all(t_env *e);

// draw.c functions
void			erase_image(t_env *e);
void			fill_pixel(t_env *e, int color, int x, int y);
void			draw(t_env *e);

// compute.c functions
int				compute(t_env *e, int x, int y);
t_vector	get_ray_dir(t_env *e, int x, int y);
int 			get_intersection(t_env *e, t_ray *ray);

// vector.c functions
void			normalize(t_vector *vector);
float     dot_product(t_vector *v1, t_vector *v2);

#endif
