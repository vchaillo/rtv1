/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 16:04:11 by valentin          #+#    #+#             */
/*   Updated: 2017/01/08 06:14:14 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			hit_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float		t;

	if (cylinder->axis == X_AXIS)
		t = hit_x_axis_cylinder(cylinder, ray);
	else if (cylinder->axis == Y_AXIS)
		t = hit_y_axis_cylinder(cylinder, ray);
	else
		t = hit_z_axis_cylinder(cylinder, ray);
	return (t);
}

float			hit_x_axis_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float		t;
	double		a;
	double		b;
	double		c;

	a = (ray->d.y * ray->d.y);
	a += (ray->d.z * ray->d.z);
	b = 2 * (ray->o.y - cylinder->pos.y) * ray->d.y;
	b += 2 * (ray->o.z - cylinder->pos.z) * ray->d.z;
	c = ((ray->o.y - cylinder->pos.y) * (ray->o.y - cylinder->pos.y));
	c += ((ray->o.z - cylinder->pos.z) * (ray->o.z - cylinder->pos.z));
	c -= cylinder->r * cylinder->r;
	t = solve_deg2(a, b, c);
	return (t);
}
float			hit_y_axis_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float		t;
	double		a;
	double		b;
	double		c;

	a = (ray->d.x * ray->d.x);
	a += (ray->d.z * ray->d.z);
	b = 2 * (ray->o.x - cylinder->pos.x) * ray->d.x;
	b += 2 * (ray->o.z - cylinder->pos.z) * ray->d.z;
	c = ((ray->o.x - cylinder->pos.x) * (ray->o.x - cylinder->pos.x));
	c += ((ray->o.z - cylinder->pos.z) * (ray->o.z - cylinder->pos.z));
	c -= cylinder->r * cylinder->r;
	t = solve_deg2(a, b, c);
	return (t);
}
float			hit_z_axis_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float		t;
	double		a;
	double		b;
	double		c;

	a = (ray->d.x * ray->d.x);
	a += (ray->d.y * ray->d.y);
	b = 2 * (ray->o.x - cylinder->pos.x) * ray->d.x;
	b += 2 * (ray->o.y - cylinder->pos.y) * ray->d.y;
	c = ((ray->o.x - cylinder->pos.x) * (ray->o.x - cylinder->pos.x));
	c += ((ray->o.y - cylinder->pos.y) * (ray->o.y - cylinder->pos.y));
	c -= cylinder->r * cylinder->r;
	t = solve_deg2(a, b, c);
	return (t);
}
