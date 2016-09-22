#include "rtv1.h"

void	init_all(t_env *e)
{
	e->background = BLACK;
	e->nb_rays = 0;

	e->camera.x = 0;
	e->camera.y = 1;
	e->camera.z = 10;

	e->screen.ratio = (float)WIN_W / (float)WIN_H;
	e->screen.fov = tan((20 * 3.14) / 180);
	e->screen.focale = 1;

	e->sphere.x = 0;
	e->sphere.y = 0;
	e->sphere.z = 0;
	e->sphere.r = 2;
	e->sphere.color = LIGHT_BLUE;

	e->plan.a = 1;
	e->plan.b = 1;
	e->plan.c = 0;
	e->plan.d = 0;
	e->plan.color = DARK_GREY;
}
