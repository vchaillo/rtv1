/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:46 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/06 23:02:14 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object		*new_object(int type, void *object, t_color *color)
{
	t_object	*new_object;

	if (!(new_object = (t_object*)malloc(sizeof(t_object))))
		print_error(MALLOC_ERROR);
	new_object->type = type;
	new_object->object = object;
	new_object->color = color;
	return (new_object);
}

void			add_object(t_scene *scene, t_object *new)
{
	if (scene->objects == NULL)
	{
		scene->objects = new;
		scene->objects->next = NULL;
	}
	else
	{
		new->next = scene->objects;
		scene->objects = new;
	}
}

void			delete_objects(t_object *objects)
{
	t_object	*tmp;

	while (objects != NULL)
	{
		tmp = objects->next;
		if (objects->type == SPHERE)
			delete_sphere(objects->object);
		else if (objects->type == PLANE)
			delete_plane(objects->object);
		delete_color(objects->color);
		objects->next = NULL;
		free(objects);
		objects = tmp;
	}
}
