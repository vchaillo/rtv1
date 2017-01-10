/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:30:24 by valentin          #+#    #+#             */
/*   Updated: 2017/01/10 17:38:15 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			hit_cone(t_cone *cone, t_ray *ray)
{
	float		t;
	double		a;
	double		b;
	double		c;

	// tangle = tan(o->radius / 2.00f);
	// dist = v3f_sub(r->start, o->position);
	// tmp[0] = v3f_dot(r->dir, o->rotation);
	// tmp[1] = v3f_dot(dist, o->rotation);
	// abc[0] = v3f_dot(r->dir, r->dir) - ((1 + POW2(tangle)) * POW2(tmp[0]));
	// abc[1] = 2 * (v3f_dot(r->dir, dist) - ((1 + POW2(tangle)) * tmp[0] * tmp[1]));
	// abc[2] = v3f_dot(dist, dist) - ((1 + POW2(tangle)) * POW2(tmp[1]));
	// det = abc[1] * abc[1] - (4 * abc[0] * abc[2]);
	// if (det < 0.00001f)
	// 	return (-1);
	// else
	// 	return (resolve_quadratic(det, abc[0], abc[1], t));

	a = ray->d.x * ray->d.x + ray->d.y * ray->d.y - ray->d.z * ray->d.z
		* tan(cone->angle) * tan(cone->angle);
	b = 2 * (ray->o.x * ray->d.x + ray->o.y * ray->d.y - ray->d.x * cone->apex.x
		- ray->d.y * cone->apex.y + (ray->d.z * (cone->apex.z - ray->o.z))
		* tan(cone->angle) * tan(cone->angle));
	c = ray->o.x * ray->o.x + ray->o.y * ray->o.y + cone->apex.x * cone->apex.x
		+ cone->apex.y * cone->apex.y - 2
			* (ray->o.x * cone->apex.x + ray->o.y * cone->apex.y)
		- (ray->o.z * ray->o.z - 2 * (ray->o.z * cone->apex.z)
			+ cone->apex.z * cone->apex.z)
		* tan(cone->angle) * tan(cone->angle);
	t = solve_deg2(a, b, c);
	if (t < 0)
		t -= t;
	return (t);
}
