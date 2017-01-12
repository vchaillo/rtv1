/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:30:24 by valentin          #+#    #+#             */
/*   Updated: 2017/01/12 18:17:45 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			hit_cone(t_cone *cone, t_ray *ray)
{
	float		t;
	double		a;
	double		b;
	double		c;

	a = pow_2(ray->d.x) + pow_2(ray->d.y) - pow_2(ray->d.z) * pow_2(tan(cone->angle));
	b = 2 * (ray->o.x * ray->d.x + ray->o.y * ray->d.y - ray->d.x * cone->apex.x
		- ray->d.y * cone->apex.y + (ray->d.z * (cone->apex.z - ray->o.z))
		* tan(cone->angle) * tan(cone->angle));
	c = pow_2(ray->o.x) + pow_2(ray->o.y) + pow_2(cone->apex.x)
		+ pow_2(cone->apex.y)
		- 2	* (ray->o.x * cone->apex.x + ray->o.y * cone->apex.y)- (pow_2(ray->o.z)
		- 2 * (ray->o.z * cone->apex.z) + cone->apex.z * cone->apex.z)
		* pow_2(tan(cone->angle));
	t = solve_deg2(a, b, c);
	if (t < 0)
		t -= t;
	return (t);
}
