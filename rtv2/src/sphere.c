/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 20:50:01 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 20:56:45 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			solve_deg2(double a, double b, double c)
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
	// printf("delta : %f\n", delta);
	return (res);
}

float			hit_sphere(t_sphere *sphere, t_ray *ray)
{
	float		t;
	double		a;
	double		b;
	double		c;

	a = dot_product(ray->d, ray->d);
	b = 2 * ray->d->x * (ray->o->x - sphere->pos->x);
	b += 2 * ray->d->y * (ray->o->y - sphere->pos->y);
	b += 2 * ray->d->z * (ray->o->z - sphere->pos->z);
	c = (ray->o->x - sphere->pos->x) * (ray->o->x - sphere->pos->x);
	c += (ray->o->y - sphere->pos->y) * (ray->o->y - sphere->pos->y);
	c += (ray->o->z - sphere->pos->z) * (ray->o->z - sphere->pos->z);
	c -= sphere->r * sphere->r;
	t = solve_deg2(a, b, c);
	return (t);
}
