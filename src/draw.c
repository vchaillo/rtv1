#include "rtv1.h"

void	erase_image(t_env *e)
{
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->size), &(e->endian));
	draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void	fill_pixel(t_env *e, t_color color, int x, int y)
{
	int		i;
	int 	color_int;

	color_int = get_color_value(color);
	i = x * 4 + y * e->size;
	e->data[i] = (color_int % 256);
	color_int /= 256;
	e->data[i + 1] = (color_int % 256);
	color_int /= 256;
	e->data[i + 2] = (color_int % 256);
}

void	draw(t_env *e)
{
	int				x;
	int				y;
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
	e->nb_rays += WIN_H * WIN_W;
}
