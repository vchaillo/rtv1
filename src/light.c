/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 22:41:26 by vchaillo          #+#    #+#             */
/*   Updated: 2016/11/21 13:59:25 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color			*diffuse(t_object *objects, t_light *spot, t_hitpoint hitpoint)
{
	t_color		*color;
	t_ray		ray;
	float		cos_angle;

	color = new_color(0);
	ray.o = hitpoint.pos;
	if (spot->dir == NULL)
		ray.d = vector_sub(spot->pos, hitpoint.pos);
	else
		ray.d = spot->dir;
	ray.t = get_ray_intersection(objects, &ray);
	ray.t = 1000;
	if (ray.t == 1000)
	{
		// ray.t = sqrt((ray.d->x * ray.d->x) + (ray.d->y * ray.d->y) + (ray.d->z * ray.d->z));
		// if (ray.t < MAX_DIST)
		// {
			cos_angle = dot_product(hitpoint.normal, normalize(ray.d));
			if (cos_angle < 0)
				cos_angle = 0;
			color = scalar_color(cos_angle, mult_color(hitpoint.color, spot->color));
		// }
	}
	return (color);
}

t_color			*illuminate(t_scene *scene, t_hitpoint hitpoint)
{
	t_color		*color;
	t_light		*light;

	color = new_color(0);
	light = scene->lights;
	while (light != NULL)
	{
		if (light->type == AMB && scene->amb == ACTIVE)
			color = add_color(scalar_color(light->intensity,
				mult_color(light->color, hitpoint.color)), color);
		else if (light->type == SPOT && scene->spot == ACTIVE)
			color = add_color(scalar_color(light->intensity,
				diffuse(scene->objects, light, hitpoint)), color);
		else if (light->type == DIR && scene->dir == ACTIVE)
			color = add_color(scalar_color(light->intensity,
				diffuse(scene->objects, light, hitpoint)), color);
		light = light->next;
	}
	return (color);
}
