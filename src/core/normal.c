/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 03:18:42 by valentin          #+#    #+#             */
/*   Updated: 2017/01/12 22:59:51 by vchaillo         ###   ########.fr       */
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

	(void)cone;
	v = vector_sub(ray->hitpoint.pos,
		((t_cone *)ray->hitpoint.object->object)->apex);
	dot = dot_product(v, ((t_cone *)ray->hitpoint.object->object)->axis);
	normal = vector_sub(v, vector_scalar(dot,
		((t_cone *)ray->hitpoint.object->object)->axis));
	return (normalize(normal));
}
