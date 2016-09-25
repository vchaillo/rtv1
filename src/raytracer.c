#include "rtv1.h"

int			get_ray_intersection(t_env *e, t_ray *ray)
{
	float				t;
	float				tsphere;
	float				tplan;

	t = 1000;
	ray->hit = FALSE;
	tsphere = hit_sphere(e, ray);
	if (tsphere > 0)
	{
		ray->hit = TRUE;
		ray->hitpoint.diffuse_color = e->sphere.color;
		t = tsphere;
	}

	tplan = hit_plan(e, ray);
	if (tplan > 0 && tplan < t)
	{
		ray->hit = TRUE;
		ray->hitpoint.diffuse_color = e->plan.color;
		t = tplan;
	}
	return (t);
}

t_vector	get_ray_dir(t_env *e, int x, int y)
{
	t_vector dir;

	dir.vx = (2.0 * ((x + 0.5) / WIN_W) - 1.0) * e->camera.ratio * e->camera.fov;
	dir.vy = (1.0 - 2.0 * ((y + 0.5) / WIN_H)) * e->camera.fov;
	dir.vz = -1;
	dir = normalize(dir);
	return (dir);
}

t_color		raytracer(t_env *e, int x, int y)
{
	t_ray	ray;

	ray.o = e->camera.pos;
	ray.d = get_ray_dir(e, x, y);
	ray.t = get_ray_intersection(e, &ray);

	if (ray.hit)
	{
		// ray.hitpoint.diffuse_color = illuminate(e, &ray);
		return (ray.hitpoint.diffuse_color);
	}
	return (e->background_color);
}
