/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 18:12:42 by valentin          #+#    #+#             */
/*   Updated: 2017/01/04 19:36:21 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			load_scene2_objects(t_scene *scene)
{
	add_object(scene, new_object(SPHERE, new_sphere(0, 2, 0, 3), new_color(WHITE), 100));
	add_object(scene, new_object(PLANE, new_plane(0, 1, 0, 2), new_color(DARK_GREY), 100));
}

void			load_scene2_lights(t_scene *scene)
{
	scene->amb_intensity = 0.5;
	scene->amb_color = new_color(WHITE);
	add_light(scene, new_light(SPOT, 1, new_vector(-10, 5, 5), new_color(RED)));
	add_light(scene, new_light(SPOT, 1, new_vector(10, 5, 5), new_color(BLUE)));
	add_light(scene, new_light(SPOT, 1, new_vector(0, 10, 5), new_color(GREEN)));
}

void			load_scene2(t_env *e)
{
	if (e->scene)
		delete_scene(e->scene);
	e->scene_type = SCENE_2;
	e->scene = new_scene(new_color(BLACK), new_camera(0, 4, 20));
	load_scene2_objects(e->scene);
	load_scene2_lights(e->scene);
}
