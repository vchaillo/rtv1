/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 18:21:38 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 20:57:07 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				get_ray_intersection(t_object *objects, t_ray *ray)
{
	float		t;
	float		tmin;
	t_object	*object;

	tmin = 1000;
	ray->hitpoint.object = NULL;
	object = objects;
	while (object != NULL)
	{
		if (object->type == SPHERE)
		{
			t = hit_sphere((t_sphere *)object->object, ray);
			// printf("sphere : %f, %f, %f\n", ((t_sphere *)object->object)->pos->x, ((t_sphere *)object->object)->pos->y, ((t_sphere *)object->object)->pos->z);
		}
		else if (object->type == PLANE)
		{
			t = hit_plane((t_plane *)object->object, ray);
		}
		if (t > 0.01 && t < tmin)
		{
			tmin = t;
			ray->hitpoint.object = object;
			ray->hitpoint.pos = vector_add(ray->o, vector_scalar(t, ray->d));
			if (object->type == SPHERE)
			{
				ray->hitpoint.normal = vector_sub(ray->hitpoint.pos, ((t_sphere *)object->object)->pos);
			}
			else if (object->type == PLANE)
			{
				ray->hitpoint.normal = ((t_plane *)object->object)->normal;
			}
			ray->hitpoint.color = object->color;
		}
		object = object->next;
	}
	return (tmin);
}

t_vector		*get_ray_dir(t_camera *camera, int x, int y)
{
	t_vector	*dir;

	dir = new_vector(0, 0, 0);
	dir->x = (2.0 * ((x + 0.5) / WIN_W) - 1.0) * camera->ratio * camera->fov;
	dir->y = (1.0 - 2.0 * ((y + 0.5) / WIN_H)) * camera->fov;
	dir->z = -camera->focale;
	dir = normalize(dir);
	return (dir);
}

t_color			*raytracer(t_scene *scene, int x, int y)
{
	t_ray		ray;

	ray.o = scene->camera->pos;
	ray.d = get_ray_dir(scene->camera, x, y);
	ray.t = get_ray_intersection(scene->objects, &ray);

	if (ray.hitpoint.object)
	{
		// ray.hitpoint.color = illuminate(e, &ray);
		printf("color :%x%x%x\n", ray.hitpoint.color->r, ray.hitpoint.color->g, ray.hitpoint.color->b);
		return (ray.hitpoint.color);
	}
	return (scene->background_color);
}
