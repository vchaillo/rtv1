#include "rtv1.h"

int			get_ray_intersection(t_env *e, t_ray *ray)
{
	float				t;
	float				tsphere;
	float				tplan;

	t = 1000;
	ray->color = e->background;
	tsphere = hit_sphere(e, ray);
	if (tsphere)
	{
		ray->color = e->sphere.color;
		t = tsphere;
	}

	tplan = hit_plan(e, ray);
	if (tplan > 0 && tplan < t)
	{
		ray->color = e->plan.color;
		t = tplan;
	}
	return (t);
}

t_vector	get_ray_dir(t_env *e, int x, int y)
{
	t_vector dir;

	dir.vx = (2.0 * ((x + 0.5) / WIN_W) - 1.0) * e->screen.ratio * e->screen.fov;
	dir.vy = (1.0 - 2.0 * ((y + 0.5) / WIN_H)) * e->screen.fov;
	dir.vz = -1;
	normalize(&dir);
	return (dir);
}

int				raytracer(t_env *e, int x, int y)
{
	t_ray	ray;

	ray.o = e->camera;
	ray.d = get_ray_dir(e, x, y);
	ray.t = get_ray_intersection(e, &ray);
	return (ray.color);
}
