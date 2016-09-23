#include "rtv1.h"

float			solve_deg2(double a, double b, double c)
{
	float		  delta;
	float		  res;
	float	 	  x1;
	float		  x2;

	delta = (b * b) - (4 * a * c);
	if (delta > 0)
	{
		x1 = (-b - sqrt(delta)) / (2 * a);
		x2 = (-b + sqrt(delta)) / (2 * a);
		if (x1 < x2)
			res = x1;
		else
			res = x2;
	}
	else if (delta == 0)
		res = -b / (2 * a);
	else
		res = 0;
	return (res);
}

t_vector 		get_sphere_hitpoint_norm(t_sphere sphere, t_hitpoint hitpoint)
{
	t_vector			norm;

	hitpoint.norm.vx = hitpoint.pos.x + -sphere.pos.x;
	hitpoint.norm.vy = hitpoint.pos.y + -sphere.pos.y;
	hitpoint.norm.vz = hitpoint.pos.z + -sphere.pos.z;
	norm = normalize(norm);
	return (norm);
}

float  		  hit_sphere(t_env *e, t_ray *ray)
{
  float				t;
	double			a;
	double			b;
	double			c;

  a = ray->d.vx * ray->d.vx + ray->d.vy * ray->d.vy + ray->d.vz * ray->d.vz;
	b = 2 * ray->d.vx * (ray->o.x - e->sphere.pos.x);
	b += 2 * ray->d.vy * (ray->o.y - e->sphere.pos.y);
	b += 2 * ray->d.vz * (ray->o.z - e->sphere.pos.z);
	c = (ray->o.x - e->sphere.pos.x) * (ray->o.x - e->sphere.pos.x);
	c += (ray->o.y - e->sphere.pos.y) * (ray->o.y - e->sphere.pos.y);
	c += (ray->o.z - e->sphere.pos.z) * (ray->o.z - e->sphere.pos.z);
	c -= e->sphere.r * e->sphere.r;
	t = solve_deg2(a, b, c);
	if (t > 0)
	{
		ray->hitpoint.pos.x = ray->o.x + ray->d.vx * t;
		ray->hitpoint.pos.y = ray->o.y + ray->d.vy * t;
		ray->hitpoint.pos.z = ray->o.z + ray->d.vz * t;
		ray->hitpoint.norm = get_sphere_hitpoint_norm(e->sphere, ray->hitpoint);
	}
  return (t);
}
