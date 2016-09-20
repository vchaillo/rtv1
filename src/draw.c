/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 21:44:52 by vchaillo          #+#    #+#             */
/*   Updated: 2016/05/19 22:09:59 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	erase_image(t_env *e)
{
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->size), &(e->endian));
	draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void	fill_pixel(t_env *e, int color, int x, int y)
{
	int		i;

	i = x * 4 + y * e->size;
	e->data[i] = color % 256;
	color /= 256;
	e->data[i + 1] = color % 256;
	color /= 256;
	e->data[i + 2] = color % 256;
}

void	draw(t_env *e)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			color = compute(e, x, y);
			fill_pixel(e, color, x, y);
			x++;
		}
		y++;
	}
	e->nb_rays += WIN_H * WIN_W;
	ft_putstr("\nNombre de rayons lancés : ");
	ft_putnbr(e->nb_rays);
	ft_putchar('\n');
}
