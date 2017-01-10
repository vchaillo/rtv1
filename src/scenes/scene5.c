/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 18:12:42 by valentin          #+#    #+#             */
/*   Updated: 2017/01/10 14:35:30 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			load_scene5_objects(t_scene *scene)
{
	add_object(scene, new_object(SPHERE, new_sphere(-4, 6, 0, 3),
		new_color(GREEN), 100));
	add_object(scene, new_object(SPHERE, new_sphere(4, 10, -2, 3),
		new_color(RED), 100));
	add_object(scene, new_object(SPHERE, new_sphere(0, 3, 10, 3),
		new_color(LIGHT_BLUE), 100));
	add_object(scene, new_object(SPHERE, new_sphere(7, 12, 4, 3),
		new_color(PURPLE), 100));
	add_object(scene, new_object(PLANE, new_plane(0, 1, 0, 0),
		new_color(DARK_GREY), 100));
}

void			load_scene5_lights(t_scene *scene)
{
	scene->amb_intensity = 0.3;
	scene->amb_color = new_color(BLUE);
	add_light(scene, new_light(SPOT, 1, new_vector(-10, 35, 40),
		new_color(WHITE)));
}

void			load_scene5(t_env *e)
{
	if (e->scene)
		delete_scene(e->scene);
	e->scene_type = SCENE_5;
	e->scene = new_scene(new_color(BLACK), new_camera(0, 7, 40));
	load_scene5_objects(e->scene);
	load_scene5_lights(e->scene);
}
