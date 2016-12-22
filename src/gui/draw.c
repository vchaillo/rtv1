/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:05 by vchaillo          #+#    #+#             */
/*   Updated: 2016/11/24 05:54:51 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	fill_pixel(t_env *e, t_color color, int x, int y)
{
	int			i;

	i = x * 4 + y * e->size;
	e->data[i] = (color.b);
	e->data[i + 1] = (color.g);
	e->data[i + 2] = (color.r);
}

void	erase_image(t_env *e)
{
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->size), &(e->endian));
	draw(e);
	e->nb_cam_rays = WIN_H * WIN_W;
	e->nb_rays = e->nb_cam_rays + e->nb_light_rays;
	if (e->verbose == TRUE)
	{
		ft_putchar('\n');
		ft_putnbr(e->nb_rays);
		ft_putendl(" Rays");
		ft_putnbr(e->nb_cam_rays);
		ft_putendl(" Cam rays");
		ft_putnbr(e->nb_light_rays);
		ft_putendl(" Light rays\n");
	}
}

void	draw(t_env *e)
{
	int			x;
	int			y;
	t_color		color;

	e->nb_rays = 0;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			color = raytracer(e, x, y);
			fill_pixel(e, color, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}