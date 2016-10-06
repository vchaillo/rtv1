/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:09 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 20:50:23 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 				init_objects(t_scene *scene)
{
	// add_object(scene, new_object(SPHERE, new_sphere(-3, 2, 0, 2), new_color(BLUE)));
	// add_object(scene, new_object(SPHERE, new_sphere(-3, 2, 0, 2), new_color(BLUE)));
	add_object(scene, new_object(SPHERE, new_sphere(1, 1, 1, 2), new_color(GREEN)));
	add_object(scene, new_object(PLANE, new_plane(0, 1, 0, 0), new_color(WHITE)));
}

void 				init_lights(t_scene *scene)
{
	add_light(scene, new_light(AMB, 0.1, NULL, NULL, new_color(WHITE)));
	add_light(scene, new_light(SPOT, 0.5, new_vector(25, 25, 25), NULL, new_color(WHITE)));
	add_light(scene, new_light(SPOT, 0.5, new_vector(-25, 25, 25), NULL, new_color(WHITE)));
	add_light(scene, new_light(DIR, 0.5, NULL, new_vector(-25, 25, 25), new_color(WHITE)));
}

void				init_all(t_env *e)
{
	e->nb_rays = 0;
	e->amb = ACTIVE;
	e->dir = ACTIVE;
	e->spot = ACTIVE;

	e->scene = new_scene(new_color(BLACK), new_camera(0, 2, 15));
	init_objects(e->scene);
	display_objects(e->scene);
	init_lights(e->scene);
	display_lights(e->scene);
}
