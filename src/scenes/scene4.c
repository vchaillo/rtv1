/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 18:12:42 by valentin          #+#    #+#             */
/*   Updated: 2017/01/10 14:35:28 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			load_scene4_objects(t_scene *scene)
{
	add_object(scene, new_object(CYLINDER, new_cylinder(X_AXIS,
		new_vector(0, 0, 0), 0.02), new_color(RED), 100));
	add_object(scene, new_object(CYLINDER, new_cylinder(Y_AXIS,
		new_vector(0, 0, 0), 0.02), new_color(GREEN), 100));
	add_object(scene, new_object(CYLINDER, new_cylinder(Z_AXIS,
		new_vector(0, 0, 0), 0.02), new_color(BLUE), 100));
}

void			load_scene4_lights(t_scene *scene)
{
	scene->amb_intensity = 0.5;
	scene->amb_color = new_color(DARK_GREY);
	add_light(scene, new_light(SPOT, 1, new_vector(-10, 5, 10),
		new_color(WHITE)));
	add_light(scene, new_light(SPOT, 1, new_vector(10, 5, 10),
		new_color(WHITE)));
}

void			load_scene4(t_env *e)
{
	if (e->scene)
		delete_scene(e->scene);
	e->scene_type = SCENE_4;
	e->scene = new_scene(new_color(BLACK), new_camera(2, 4, 20));
	e->scene->camera->rot.x += 0.2;
	e->scene->camera->rot.y -= 0.1;
	load_scene4_objects(e->scene);
	load_scene4_lights(e->scene);
}
