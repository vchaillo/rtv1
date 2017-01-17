/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 03:18:42 by valentin          #+#    #+#             */
/*   Updated: 2017/01/17 09:38:02 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		get_normal(t_ray *ray)
{
	t_vector	normal;

	if (ray->hitpoint.object->type == SPHERE)
		normal = normalize(vector_sub(ray->hitpoint.pos,
			((t_sphere *)ray->hitpoint.object->object)->pos));
	else if (ray->hitpoint.object->type == PLANE)
		normal = normalize(((t_plane *)ray->hitpoint.object->object)->normal);
	else if (ray->hitpoint.object->type == CYLINDER)
		normal = get_normal_at_cylinder(ray, ray->hitpoint.object->object);
	else
		normal = get_normal_at_cone(ray, ray->hitpoint.object->object);
	return (normal);
}

t_vector		get_normal_at_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_vector	normal;
	t_vector	dist;
	float		dot;

	dist = vector_sub(ray->o, cylinder->pos);
	dot = dot_product(ray->d, cylinder->axis) *
		ray->t + dot_product(dist, cylinder->axis);
	normal = vector_add(vector_scalar(ray->t, ray->d), dist);
	normal = vector_sub(normal, vector_scalar(dot, cylinder->axis));
	return (normalize(normal));
}

t_vector		get_normal_at_cone(t_ray *ray, t_cone *cone)
{
	t_vector	v;
	t_vector	normal;
	float		dot;

	v = vector_sub(ray->hitpoint.pos, cone->apex);
	dot = dot_product(v, cone->axis);
	normal = vector_sub(v, vector_scalar(dot, cone->axis));
	return (normalize(normal));
	// t_vector	normal;
	// t_vector	dist;
	// t_vector	tmp;
	// float		dot;
	//
	// dist = vector_sub(ray->o, cone->apex);
	// dot = dot_product(ray->d, cone->axis) * ray->t
	// 	+ dot_product(dist, cone->axis);
	// normal = vector_scalar(ray->t, ray->d);
	// normal = vector_add(normal, dist);
	// tmp = vector_scalar(dot * (1 + pow_2(tan(cone->angle / 2))), cone->axis);
	// normal = vector_sub(normal, tmp);
	// return (normalize(normal));
}
