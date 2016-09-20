/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 21:23:00 by vchaillo          #+#    #+#             */
/*   Updated: 2016/05/19 21:58:08 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			solve_equation(double a, double b, double c)
{
	float		delta;
	float		res;
	float		x1;
	float		x2;

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
	if (res < 0.01)
		res = 0;
	return (res);
}

int			get_intersection(t_env *e, t_ray *ray)
{
	float		t;
	float		p;
	double	a;
	double	b;
	double	c;

	a = ray->d.vx * ray->d.vx + ray->d.vy * ray->d.vy + ray->d.vz * ray->d.vz;
	b = 2 * ray->d.vx * (ray->o.x - e->sphere.x);
	b += 2 * ray->d.vy * (ray->o.y - e->sphere.y);
	b += 2 * ray->d.vz * (ray->o.z - e->sphere.z);
	c = (ray->o.x - e->sphere.x) * (ray->o.x - e->sphere.x);
	c += (ray->o.y - e->sphere.y) * (ray->o.y - e->sphere.y);
	c += (ray->o.z - e->sphere.z) * (ray->o.z - e->sphere.z);
	c -= e->sphere.r * e->sphere.r;
	t = solve_equation(a, b, c);

	// p = -(e->plan.a*ray->d.vx + e->plan.b*ray->d.vy + e->plan.c*ray->d.vz) + (e->plan.a*ray->o.x + e->plan.b*ray->o.y + e->plan.c*ray->o.z + e->plan.d);
	p = -((e->plan.a * (ray->o.x - e->plan.a) + e->plan.b * (ray->o.y - e->plan.b) + e->plan.c * (ray->o.z - e->plan.c) + e->plan.d) / (e->plan.a * ray->d.vx + e->plan.a * ray->d.vy + e->plan.a * ray->d.vz));
	if (p >= 0.01 && t != 0 && p < t)
		return (e->plan.color);
	else if (t == 0)
		return (e->background);
	else
		return (e->sphere.color);
}

t_vector	get_ray_dir(t_env *e, int x, int y)
{
	t_vector dir;
	double		xn;
	double		yn;

	xn = (x + 0.5) / WIN_W;
	yn = (y + 0.5) / WIN_H;
	dir.vx = (2.0 * xn - 1.0) * e->screen.iar * e->screen.fov;
	dir.vy = (1.0 - 2.0 * yn) * e->screen.fov;
	dir.vz = -1;
	normalize(&dir);
	return (dir);
}

int				compute(t_env *e, int x, int y)
{
	t_ray	ray;

	ray.o = e->camera;
	ray.d = get_ray_dir(e, x, y);
	ray.t = get_intersection(e, &ray);
	// if (ray.t == 0)
	// 	return e->background;
	// else
	// 	return e->sphere.color;
	return (ray.t);
}
