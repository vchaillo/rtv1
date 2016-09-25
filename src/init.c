#include "rtv1.h"

void init_test_scene(t_env *e)
{
	e->camera.pos.x = 0;
	e->camera.pos.y = 1;
	e->camera.pos.z = 5;

	e->amb.type = AMB;
	e->amb.color = new_color(WHITE);

	e->spot.type = SPOT;
	e->spot.pos.x = 5;
	e->spot.pos.y = 5;
	e->spot.pos.z = 15;
	e->spot.color = new_color(WHITE);

	e->sphere.pos.x = 0;
	e->sphere.pos.y = 1;
	e->sphere.pos.z = 0;
	e->sphere.r = 1;
	e->sphere.color = new_color(RED);

	e->plan.norm.vx = 0;
	e->plan.norm.vy = 1;
	e->plan.norm.vz = 0;
	e->plan.d = 0;
	e->plan.color = new_color(DARK_GREY);
}

void	init_all(t_env *e)
{
	e->background_color = new_color(BLACK);
	e->nb_rays = 0;

	e->camera.ratio = RATIO;
	e->camera.fov = FOV;
	e->camera.focale = FOCALE;

	init_test_scene(e);
}
