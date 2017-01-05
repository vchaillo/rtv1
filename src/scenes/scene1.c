/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 18:12:42 by valentin          #+#    #+#             */
/*   Updated: 2017/01/05 02:54:32 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			load_scene1_objects(t_scene *scene)
{
	add_object(scene, new_object(SPHERE, new_sphere(0, 2, 0, 3), new_color(YELLOW), 10));
	add_object(scene, new_object(CYLINDER, new_cylinder(new_vector(1, 1, 0), new_vector(4, 0, -4), 1), new_color(RED), 100));
	add_object(scene, new_object(CYLINDER, new_cylinder(new_vector(0, 1, 0), new_vector(-4, 0, -4), 1), new_color(RED), 100));
	add_object(scene, new_object(PLANE, new_plane(0, 1, 0, 2), new_color(DARK_GREY), 1000));
}

void			load_scene1_lights(t_scene *scene)
{
	scene->amb_intensity = 0.5;
	scene->amb_color = new_color(WHITE);
	add_light(scene, new_light(SPOT, 1, new_vector(-15, 10, 20), new_color(WHITE)));
	add_light(scene, new_light(DIR, 0.1, new_vector(-1, -1, -1), new_color(WHITE)));
}

void			load_scene1(t_env *e)
{
	if (e->scene)
		delete_scene(e->scene);
	e->scene_type = SCENE_1;
	e->scene = new_scene(new_color(BLACK), new_camera(0, 4, 20));
	load_scene1_objects(e->scene);
	load_scene1_lights(e->scene);
}
