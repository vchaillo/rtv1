/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 03:18:42 by valentin          #+#    #+#             */
/*   Updated: 2017/01/09 19:49:50 by valentinchaillou89###   ########.fr       */
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
		normal = get_normal_at_cylinder(ray);
	else if (ray->hitpoint.object->type == CONE)
		normal = get_normal_at_cone(ray);
	return (normal);
}

t_vector		get_normal_at_cone(t_ray *ray)
{
	t_vector	v;
	float		dot;
	t_vector	normal;

	v = vector_sub(ray->hitpoint.pos,
		((t_cone *)ray->hitpoint.object->object)->apex);
	dot = dot_product(v, ((t_cone *)ray->hitpoint.object->object)->axis);
	normal = vector_sub(v, vector_scalar(dot,
		 ((t_cone *)ray->hitpoint.object->object)->axis));
	return (normalize(normal));
}

t_vector		get_normal_at_cylinder(t_ray *ray)
{
	t_vector	normal;

	if (((t_cylinder *)ray->hitpoint.object->object)->axis == X_AXIS)
	{
		normal = normalize(vector_sub(new_vector(
			0, ray->hitpoint.pos.y, ray->hitpoint.pos.z),
			((t_cylinder *)ray->hitpoint.object->object)->pos));
	}
	else if (((t_cylinder *)ray->hitpoint.object->object)->axis == Y_AXIS)
	{
		normal = normalize(vector_sub(new_vector(
			ray->hitpoint.pos.x, 0, ray->hitpoint.pos.z),
			((t_cylinder *)ray->hitpoint.object->object)->pos));
	}
	else
	{
		normal = normalize(vector_sub(new_vector(
			ray->hitpoint.pos.x, ray->hitpoint.pos.y, 0),
			((t_cylinder *)ray->hitpoint.object->object)->pos));
	}
	return (normal);
}
