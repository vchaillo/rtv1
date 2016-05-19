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
# include "libft.h"

# define WIN_W 1920
# define WIN_H 1080

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			size;
	int			endian;
	int			bpp;
}				t_env;

/*
** mlx.c functions
*/
void			start_mlx(t_env *e);
int				mouse_hook(int button, int x, int y, t_env *e);
int				key_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);
/*
** draw.c functions
*/
void			erase_image(t_env *e);
void			fill_pixel(t_env *e, int color, int x, int y);

#endif
