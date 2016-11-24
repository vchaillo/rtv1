/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:09 by vchaillo          #+#    #+#             */
/*   Updated: 2016/11/24 21:33:07 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				init_objects(t_scene *scene)
{
	add_object(scene, new_object(SPHERE, new_sphere(0, 2, 0, 2), new_color(PASTEL_BLUE)));
	add_object(scene, new_object(SPHERE, new_sphere(-4, 2, -1, 1.5), new_color(ORANGE)));
	add_object(scene, new_object(SPHERE, new_sphere(-1, 1, 3, 1), new_color(LIGHT_GREEN)));
	add_object(scene, new_object(SPHERE, new_sphere(4, 1, -4, 1), new_color(YELLOW)));
	add_object(scene, new_object(PLANE, new_plane(0, 1, 0, 0), new_color(DARK_GREY)));
	// add_object(scene, new_object(PLANE, new_plane(0, -1, 0, 6), new_color(LIGHT_GREY)));
	// add_object(scene, new_object(PLANE, new_plane(1, 0, 0, 4), new_color(LIGHT_GREY)));
	// add_object(scene, new_object(PLANE, new_plane(-1, 0, 0, 4), new_color(LIGHT_GREY)));
	// add_object(scene, new_object(PLANE, new_plane(0, 0, 1, 4), new_color(LIGHT_GREY)));
}

void				init_lights(t_scene *scene)
{
	scene->amb_intensity = 0.1;
	scene->amb_color = new_color(WHITE);
	add_light(scene, new_light(SPOT, 1, new_vector(-3, 8, 4), new_vector(-3, 8, 4), new_color(WHITE)));
	// add_light(scene, new_light(SPOT, 1, new_vector(10, 2, 10), NULL, new_color(WHITE)));
	// add_light(scene, new_light(DIR, 0.8, NULL, new_vector(1, -1, -1), new_color(WHITE)));
}

void				init_all(t_env *e)
{
	e->nb_rays = 0;
	e->nb_cam_rays = 0;
	e->nb_light_rays = 0;
	e->scene = new_scene(new_color(BLACK), new_camera(0, 2, 15));
	init_objects(e->scene);
	init_lights(e->scene);
}
