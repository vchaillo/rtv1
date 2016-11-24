/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 18:21:38 by vchaillo          #+#    #+#             */
/*   Updated: 2016/11/24 03:37:21 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			get_hitpoint(t_object *object, t_ray *ray, float tmin)
{
	ray->hitpoint.object = object;
	ray->hitpoint.pos = vector_add(ray->o, vector_scalar(tmin, ray->d));
	if (object->type == SPHERE)
		ray->hitpoint.normal = vector_sub(ray->hitpoint.pos, ((t_sphere *)object->object)->pos);
	else if (object->type == PLANE)
		ray->hitpoint.normal = ((t_plane *)object->object)->normal;
	ray->hitpoint.color = object->color;
}

int				get_ray_intersection(t_object *objects, t_ray *ray)
{
	float		t;
	float		tmin;
	t_object	*object;

	tmin = MAX_DIST;
	ray->hitpoint.object = NULL;
	object = objects;
	while (object != NULL)
	{
		if (object->type == SPHERE)
			t = hit_sphere((t_sphere *)object->object, ray);
		else if (object->type == PLANE)
			t = hit_plane((t_plane *)object->object, ray);
		if (t > EPSILON && t < tmin)
		{
			tmin = t;
			get_hitpoint(object, ray, tmin);
		}
		object = object->next;
	}
	return (tmin);
}

t_vector		*get_ray_dir(t_camera *camera, int x, int y)
{
	t_vector	*dir;
	float		dir_x;
	float		dir_y;
	float		dir_z;

	dir_x = (2.0 * ((x + 0.5) / WIN_W) - 1.0) * camera->ratio * camera->fov;
	dir_y = (1.0 - 2.0 * ((y + 0.5) / WIN_H)) * camera->fov;
	dir_z = -camera->focale;
	dir = new_vector(dir_x, dir_y, dir_z);
	dir = normalize(dir);
	return (dir);
}

t_color			raytracer(t_scene *scene, int x, int y)
{
	t_ray		ray;

	ray.o = scene->camera->pos;
	ray.d = get_ray_dir(scene->camera, x, y);
	ray.t = get_ray_intersection(scene->objects, &ray);
	if (ray.hitpoint.object)
	{
		ray.hitpoint.color = illuminate(scene, ray.hitpoint);
		return (ray.hitpoint.color);
	}
	return (scene->background_color);
}
