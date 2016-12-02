/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 16:04:11 by valentin          #+#    #+#             */
/*   Updated: 2016/12/02 00:12:07 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			hit_cylinder(t_cylinder *cylinder, t_ray *ray)
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
