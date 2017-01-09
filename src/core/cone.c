/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:30:24 by valentin          #+#    #+#             */
/*   Updated: 2017/01/09 19:31:40 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			hit_cone(t_cone *cone, t_ray *ray)
{
	float		t;
	double		a;
	double		b;
	double		c;

	a = ray->d.x * ray->d.x + ray->d.y * ray->d.y - ray->d.z * ray->d.z
		* tan(cone->angle) * tan(cone->angle);
	b = 2 * (ray->o.x * ray->d.x + ray->o.y * ray->d.y - ray->d.x * cone->apex.x
		- ray->d.y * cone->apex.y + (ray->d.z * (cone->apex.z - ray->o.z))
			* tan(cone->angle) * tan(cone->angle));
	c = ray->o.x * ray->o.x + ray->o.y * ray->o.y + cone->apex.x * cone->apex.x
		+ cone->apex.y * cone->apex.y - 2 * (ray->o.x * cone->apex.x + ray->o.y * cone->apex.y)
			- (ray->o.z * ray->o.z - 2 * (ray->o.z * cone->apex.z) + cone->apex.z * cone->apex.z)
				* tan(cone->angle) * tan(cone->angle);
	t = solve_deg2(a, b, c);
	if (t < 0)
		t -= t;
	return (t);
}
