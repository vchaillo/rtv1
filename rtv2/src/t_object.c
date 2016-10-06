/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:46 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 20:04:51 by vchaillo         ###   ########.fr       */
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

void			display_objects(t_scene *scene)
{
	t_object      *obj;

	obj = scene->objects;
	ft_putendl("\nObjects in scene");
	ft_putendl("----------------");
	while (obj != NULL)
	{
		if (obj->type == SPHERE)
		{
			t_sphere  *s;
			s = (t_sphere*)obj->object;
			printf("- SPHERE (%d, %d, %d, %d)\n", (int)s->pos->x, (int)s->pos->y, (int)s->pos->z, (int)s->r);
		}
		else if (obj->type == PLANE)
		{
			t_plane  *p;
			p = (t_plane*)obj->object;
			printf("- PLANE (%d, %d, %d, %d)\n", (int)p->normal->x, (int)p->normal->y, (int)p->normal->z, (int)p->offset);
		}
		printf("  -> COLOR (r:%x, g:%x, b:%x)\n", obj->color->r, obj->color->g, obj->color->b);
		obj = obj->next;
	}
	ft_putchar('\n');
}
