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
  return (t);
}

float  		  hit_sphere2(t_env *e, t_ray *ray)
{
  float				t;
	double			a;
	double			b;
	double			c;

  a = ray->d.vx * ray->d.vx + ray->d.vy * ray->d.vy + ray->d.vz * ray->d.vz;
	b = 2 * ray->d.vx * (ray->o.x - e->sphere2.pos.x);
	b += 2 * ray->d.vy * (ray->o.y - e->sphere2.pos.y);
	b += 2 * ray->d.vz * (ray->o.z - e->sphere2.pos.z);
	c = (ray->o.x - e->sphere2.pos.x) * (ray->o.x - e->sphere2.pos.x);
	c += (ray->o.y - e->sphere2.pos.y) * (ray->o.y - e->sphere2.pos.y);
	c += (ray->o.z - e->sphere2.pos.z) * (ray->o.z - e->sphere2.pos.z);
	c -= e->sphere2.r * e->sphere2.r;
	t = solve_deg2(a, b, c);
  return (t);
}
