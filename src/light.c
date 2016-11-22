/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 22:41:26 by vchaillo          #+#    #+#             */
/*   Updated: 2016/11/22 01:01:16 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				is_in_shadow(t_object *objects, t_ray *ray)
{
	float		t;
	t_object	*object;

	object = objects;
	while (object != NULL)
	{
		if (object->type == SPHERE)
			t = hit_sphere((t_sphere *)object->object, ray);
		else if (object->type == PLANE)
			t = hit_plane((t_plane *)object->object, ray);

		if (t > EPSILON && t < 1)
			return (1);
		object = object->next;
	}
	return (0);
}

t_color			diffuse(t_object *objects, t_light *spot, t_hitpoint hitpoint)
{
	t_color		color;
	t_ray		ray;
	float		cos_angle;

	color = new_color(BLACK);
	ray.o = hitpoint.pos;
	if (spot->dir == NULL)
		ray.d = vector_sub(spot->pos, hitpoint.pos);
	else
		ray.d = vector_scalar(-1, spot->dir);
	if (!(is_in_shadow(objects, &ray)))
	{
		cos_angle = dot_product(hitpoint.normal, normalize(ray.d));
		if (cos_angle < 0)
			cos_angle = 0;
		color = scalar_color(cos_angle, mult_color(hitpoint.color, spot->color));
		// color = add_color(, color);
	}
	return (color);
}

t_color			illuminate(t_scene *scene, t_hitpoint hitpoint)
{
	t_color		color;
	t_light		*light;

	color = new_color(BLACK);
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
