#include "rtv1.h"

void init_test_scene(t_env *e)
{
	e->camera.pos.x = 0;
	e->camera.pos.y = 3;
	e->camera.pos.z = 15;

	e->amb.type = AMB;
	e->amb.intensity = 0.1;
	e->amb.color = scalar_color(e->amb.intensity, new_color(WHITE));

	e->spot.type = SPOT;
	e->spot.pos.x = 25;
	e->spot.pos.y = 20;
	e->spot.pos.z = 25;
	e->spot.intensity = 0.5;
	e->spot.color = scalar_color(e->spot.intensity, new_color(GREEN));

	e->spot2.type = SPOT;
	e->spot2.pos.x = -25;
	e->spot2.pos.y = 20;
	e->spot2.pos.z = 25;
	e->spot2.intensity = 0.5;
	e->spot2.color = scalar_color(e->spot2.intensity, new_color(BLUE));

	e->sphere.pos.x = -2;
	e->sphere.pos.y = 2;
	e->sphere.pos.z = 0;
	e->sphere.r = 2;
	e->sphere.color = new_color(WHITE);

	e->sphere2.pos.x = 4;
	e->sphere2.pos.y = 4;
	e->sphere2.pos.z = 0;
	e->sphere2.r = 3;
	e->sphere2.color = new_color(WHITE);

	e->plan.norm.vx = 0.5;
	e->plan.norm.vy = 1;
	e->plan.norm.vz = 0;
	e->plan.d = -2;
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
