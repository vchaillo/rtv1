#include "rtv1.h"

int		expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	if (keycode == ESCAPE || keycode == ESCAPE_MAC)
		exit(0);
	else if (keycode == RETURN || keycode == RETURN_MAC)
		e->amb.intensity += 0.1;
	else if (keycode == D || keycode == D_MAC)
		e->camera.pos.x += 1;
	else if (keycode == Q || keycode == Q_MAC)
		e->camera.pos.x -= 1;
	else if (keycode == SPACE || keycode == SPACE_MAC)
		e->camera.pos.y += 1;
	else if (keycode == CONTROL || keycode == CONTROL_MAC)
		e->camera.pos.y -= 1;
	else if (keycode == S || keycode == S_MAC)
		e->camera.pos.z += 1;
	else if (keycode == Z || keycode == Z_MAC)
		e->camera.pos.z -= 1;
	else if (keycode == R || keycode == R_MAC)
		init_all(e);
	erase_image(e);
	ft_putnbr(keycode);
	ft_putchar('\n');
	return (0);
}

int		mouse_hook(int button, int x, int y, t_env *e)
{
	ft_putnbr(button);
	ft_putchar('\n');
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
	ft_putchar('\n');
	erase_image(e);
	return (0);
}

void	start_mlx(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		exit(0);
	e->win = mlx_new_window(e->mlx, WIN_W, WIN_H, "rtv1");
	e->img = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->size), &(e->endian));
	init_all(e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_hook(e->win, 3, 3, key_hook, e);
	mlx_loop(e->mlx);
}
