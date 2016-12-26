/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:09 by vchaillo          #+#    #+#             */
/*   Updated: 2016/12/27 00:05:04 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				init_objects(t_scene *scene)
{
	// add_object(scene, new_object(SPHERE, new_sphere(-4, 6, -4, 1.5), new_color(PASTEL_BLUE), 100));
	// add_object(scene, new_object(SPHERE, new_sphere(4, 6, -4, 1.5), new_color(PASTEL_BLUE), 100));
	// add_object(scene, new_object(SPHERE, new_sphere(-4, 0, -4, 1.5), new_color(LIGHT_GREEN), 100));
	// add_object(scene, new_object(SPHERE, new_sphere(4, 0, -4, 1.5), new_color(LIGHT_GREEN), 100));
	// add_object(scene, new_object(SPHERE, new_sphere(-4, 3, -4, 1.1), new_color(ORANGE), 100));
	// add_object(scene, new_object(SPHERE, new_sphere(4, 3, -4, 1.1), new_color(ORANGE), 100));
	add_object(scene, new_object(SPHERE, new_sphere(0, 2, 0, 3), new_color(YELLOW), 100));

	add_object(scene, new_object(CYLINDER, new_cylinder(new_vector(1, 1, 0), new_vector(4, 0, -4), 1), new_color(RED), 100));
	add_object(scene, new_object(CYLINDER, new_cylinder(new_vector(0, 1, 0), new_vector(-4, 0, -4), 1), new_color(RED), 100));
	add_object(scene, new_object(PLANE, new_plane(0, 1, 0, 2), new_color(DARK_GREY), 100));
	// add_object(scene, new_object(PLANE, new_plane(0, -1, 0, 6), new_color(DARK_GREY), 100));
	// add_object(scene, new_object(PLANE, new_plane(1, 0, 0, 4), new_color(DARK_GREY), 10));
	// add_object(scene, new_object(PLANE, new_plane(-1, 0, 0, 4), new_color(DARK_GREY), 10));
	// add_object(scene, new_object(PLANE, new_plane(0, 0, 1, 4), new_color(DARK_GREY), 10));
}

void				init_lights(t_scene *scene)
{
	scene->amb_intensity = 0.5;
	scene->amb_color = new_color(WHITE);
	add_light(scene, new_light(SPOT, 1, new_vector(-15, 10, 20), new_color(WHITE)));
	// add_light(scene, new_light(SPOT, 1, new_vector(-10, 5, 5), new_color(RED)));
	// add_light(scene, new_light(SPOT, 1, new_vector(10, 5, 5), new_color(BLUE)));
	// add_light(scene, new_light(SPOT, 1, new_vector(0, 10, 5), new_color(GREEN)));
	add_light(scene, new_light(DIR, 0.1, new_vector(-1, -1, -1), new_color(WHITE)));
}

void				init_all(t_env *e)
{
	e->nb_rays = 0;
	e->nb_cam_rays = 0;
	e->nb_light_rays = 0;
	e->scene = new_scene(new_color(BLACK), new_camera(0, 4, 20));
	init_objects(e->scene);
	init_lights(e->scene);
}
