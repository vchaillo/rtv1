#include "rtv1.h"

t_point		get_hitpoint_pos(t_ray *ray, float t)
{
	ray->hitpoint.pos.x = ray->o.x + ray->d.vx * t;
	ray->hitpoint.pos.y = ray->o.y + ray->d.vy * t;
	ray->hitpoint.pos.z = ray->o.z + ray->d.vz * t;
	return (ray->hitpoint.pos);
}

int				get_ray_intersection(t_env *e, t_ray *ray)
{
	float				t;
	float				tsphere;
	float				tplan;

	t = 1000;
	ray->hit = FALSE;
	tsphere = hit_sphere(e, ray);
	if (tsphere > 0)
	{
		t = tsphere;
		ray->hit = TRUE;
		ray->hitpoint.pos = get_hitpoint_pos(ray, t);
		ray->hitpoint.norm.vx = ray->hitpoint.pos.x - e->sphere.pos.x;
		ray->hitpoint.norm.vy = ray->hitpoint.pos.y - e->sphere.pos.y;
		ray->hitpoint.norm.vz = ray->hitpoint.pos.z - e->sphere.pos.z;
		normalize(ray->hitpoint.norm);
		ray->hitpoint.color = e->sphere.color;
	}
	tplan = hit_plan(e, ray);
	if (tplan > 0 && tplan < t)
	{
		t = tplan;
		ray->hit = TRUE;
		get_hitpoint_pos(ray, t);
		ray->hitpoint.norm.vx = e->plan.norm.vx;
		ray->hitpoint.norm.vy = e->plan.norm.vy;
		ray->hitpoint.norm.vz = e->plan.norm.vz;
		normalize(ray->hitpoint.norm);
		ray->hitpoint.color = e->plan.color;
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
		ray.hitpoint.color = illuminate(e, &ray);
		return (ray.hitpoint.color);
	}
	return (e->background_color);
}
