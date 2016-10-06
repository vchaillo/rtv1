/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:09 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/06 21:55:10 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 				init_objects(t_scene *scene)
{
	// add_object(scene, new_object(SPHERE, new_sphere(-3, 2, 0, 2), new_color(BLUE)));
	// add_object(scene, new_object(SPHERE, new_sphere(-3, 2, 0, 2), new_color(BLUE)));
	add_object(scene, new_object(SPHERE, new_sphere(0, 2, 0, 2), new_color(WHITE)));
	add_object(scene, new_object(PLANE, new_plane(0, 1, 0, 0), new_color(WHITE)));
}

void 				init_lights(t_scene *scene)
{
	add_light(scene, new_light(AMB, 0.1, NULL, NULL, new_color(WHITE)));
	add_light(scene, new_light(SPOT, 0.5, new_vector(25, 25, 25), NULL, new_color(WHITE)));
	// add_light(scene, new_light(SPOT, 0.5, new_vector(-25, 25, 25), NULL, new_color(RED)));
	// add_light(scene, new_light(SPOT, 0.5, new_vector(0, 25, 25), NULL, new_color(YELLOW)));
	// add_light(scene, new_light(SPOT, 0.5, new_vector(0, 25, -25), NULL, new_color(GREEN)));
	// add_light(scene, new_light(DIR, 0.5, NULL, new_vector(1, 1, 2), new_color(ORANGE)));
}

void				init_all(t_env *e)
{
	e->nb_rays = 0;

	e->scene = new_scene(new_color(BLACK), new_camera(0, 3, 15));
	init_objects(e->scene);
	init_lights(e->scene);
}