/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 21:44:49 by vchaillo          #+#    #+#             */
/*   Updated: 2017/01/28 14:57:57 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			load_scene1_objects(t_scene *scene)
{
	add_object(scene, new_object(SPHERE, new_sphere(-34, 10, 30, 9),
		new_color(PASTEL_BLUE), 100));
	add_object(scene, new_object(CYLINDER, new_cylinder(new_vector(0, 1, 0),
		new_vector(0, 15, 0), 10), new_color(RED), 100));
	add_object(scene, new_object(CONE, new_cone(new_vector(1, 0, -0.3),
		new_vector(20, 10, 10), 15), new_color(GREEN_4), 100));
	add_object(scene, new_object(PLANE, new_plane(0, 1, 0, 0),
		new_color(LIGHT_GREY), 100));
}

void			load_scene1_lights(t_scene *scene)
{
	scene->amb_intensity = 0.3;
	scene->amb_color = new_color(BLUE);
	add_light(scene, new_light(SPOT, 1, new_vector(-100, 25, 100),
		new_color(WHITE)));
}

void			load_scene1(t_env *e)
{
	if (e->scene)
		delete_scene(e->scene);
	e->scene_type = SCENE_1;
	e->scene = new_scene(new_color(BLACK), new_camera(0, 15, 120));
	load_scene1_objects(e->scene);
	load_scene1_lights(e->scene);
}
