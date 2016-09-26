#include "rtv1.h"

void init_test_scene(t_env *e)
{
	e->camera.pos.x = 0;
	e->camera.pos.y = 3;
	e->camera.pos.z = 15;

	e->amb.type = AMB;
	e->amb.intensity = 0.1;
	e->amb.color = scalar_color(1 - e->amb.intensity, new_color(WHITE));

	e->spot.type = SPOT;
	e->spot.pos.x = 25;
	e->spot.pos.y = 50;
	e->spot.pos.z = 50;
	e->spot.intensity = 0.1;
	e->spot.color = scalar_color(e->spot.intensity, new_color(WHITE));

	e->sphere.pos.x = 0;
	e->sphere.pos.y = 2;
	e->sphere.pos.z = 0;
	e->sphere.r = 2;
	e->sphere.color = new_color(LIGHT_BLUE);

	e->plan.norm.vx = 0;
	e->plan.norm.vy = 1;
	e->plan.norm.vz = 0;
	e->plan.d = 0;
	e->plan.color = new_color(WHITE);
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
