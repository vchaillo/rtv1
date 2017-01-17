/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:30:24 by valentin          #+#    #+#             */
/*   Updated: 2017/01/13 00:24:29 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			hit_cone(t_cone *cone, t_ray *ray)
{
	float		t;
	double		a;
	double		b;
	double		c;

	t_vector	dist;
	float		tmp[2];
	float		tangle;

	tangle = tan(cone->angle / 2);
	dist = vector_sub(ray->o, cone->apex);
	tmp[0] = dot_product(ray->d, cone->axis);
	tmp[1] = dot_product(dist, cone->axis);
	a = dot_product(ray->d, ray->d) - ((1 + pow_2(tangle)) * pow_2(tmp[0]));
	b = 2 * (dot_product(ray->d, dist) - ((1 + pow_2(tangle)) * tmp[0] * tmp[1]));
	c = dot_product(dist, dist) - ((1 + pow_2(tangle)) * pow_2(tmp[1]));
	t = solve_deg2(a, b, c);
	return (t);
}
