/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:41 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 16:30:56 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light			*new_light(int type, float intensity, t_vector *pos, t_vector *dir, t_color *color)
{
	t_light		*new_light;

	if (!(new_light = (t_light*)malloc(sizeof(t_light))))
		print_error(MALLOC_ERROR);
	new_light->type = type;
	new_light->intensity = intensity;
	new_light->pos = pos;
	new_light->dir = dir;
	new_light->color = scalar_color(intensity, color);
	return (new_light);
}

void			add_light(t_scene *scene, t_light *new)
{
	if (scene->lights == NULL)
	{
		scene->lights = new;
		scene->lights->next = NULL;
	}
	else
	{
		new->next = scene->lights;
		scene->lights = new;
	}
}

void			delete_lights(t_light *lights)
{
	t_light		*tmp;

	while (lights != NULL)
	{
		tmp = lights->next;
		delete_vector(lights->pos);
		delete_vector(lights->dir);
		delete_color(lights->color);
		lights->next = NULL;
		free(lights);
	}
}


void			display_lights(t_scene *scene)
{
	t_light		*light;

	light = scene->lights;
	ft_putendl("Lights in scene");
	ft_putendl("----------------");
	while (light != NULL)
	{
		if (light->type == SPOT)
			printf("- SPOT (%d, %d, %d)\n", (int)light->pos->x, (int)light->pos->y, (int)light->pos->z);
		else if (light->type == DIR)
			printf("- DIR (%d, %d, %d)\n", (int)light->dir->x, (int)light->dir->y, (int)light->dir->z);
		else if (light->type == AMB)
			printf("- AMB\n");
		printf("  -> INTENSITY : %f\n", light->intensity);
		printf("  -> COLOR (r:%x, g:%x, b:%x)\n", light->color->r, light->color->g, light->color->b);
		light = light->next;
	}
	ft_putchar('\n');
}
