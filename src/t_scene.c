/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:57 by vchaillo          #+#    #+#             */
/*   Updated: 2016/11/26 00:48:03 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene			*new_scene(t_color background_color, t_camera *camera)
{
	t_scene		*scene;

	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
		print_error(MALLOC_ERROR);
	scene->background_color = background_color;
	scene->camera = camera;
	scene->objects = NULL;
	scene->lights = NULL;
	scene->amb = ACTIVE;
	scene->dir = ACTIVE;
	scene->spot = ACTIVE;
	scene->diffuse = ACTIVE;
	scene->specular = ACTIVE;
	return (scene);
}

void			delete_scene(t_scene *scene)
{
	if (scene)
	{
		delete_camera(scene->camera);
		delete_objects(scene->objects);
		delete_lights(scene->lights);
		free(scene);
	}
}
