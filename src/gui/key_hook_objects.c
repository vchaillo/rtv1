/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 22:26:30 by valentin          #+#    #+#             */
/*   Updated: 2017/01/08 02:53:22 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				key_hook_plane(int keycode, t_plane *plane)
{
	if (keycode == UP || keycode == UP_MAC)
		plane->normal = vector_rot_x(plane->normal, 0.1);
	else if (keycode == DOWN || keycode == DOWN_MAC)
		plane->normal = vector_rot_x(plane->normal, -0.1);
	else if (keycode == LEFT || keycode == LEFT_MAC)
		plane->normal = vector_rot_y(plane->normal, 0.1);
	else if (keycode == RIGHT || keycode == RIGHT_MAC)
		plane->normal = vector_rot_y(plane->normal, -0.1);
	else if (keycode == A || keycode == Q_MAC)
		plane->normal = vector_rot_z(plane->normal, 0.1);
	else if (keycode == E || keycode == E_MAC)
		plane->normal = vector_rot_z(plane->normal, -0.1);
	else if (keycode == PLUS || keycode == PLUS_MAC)
		plane->offset -= 1;
	else if (keycode == MINUS || keycode == MINUS_MAC)
		plane->offset += 1;
	return (0);
}

int				key_hook_cylinder(int keycode, t_cylinder *cylinder)
{
	if (keycode == D || keycode == D_MAC)
		cylinder->pos.x += 1;
	else if (keycode == Q || keycode == A_MAC)
		cylinder->pos.x -= 1;
	else if (keycode == SPACE || keycode == SPACE_MAC)
		cylinder->pos.y += 1;
	else if (keycode == CONTROL || keycode == CONTROL_MAC)
		cylinder->pos.y -= 1;
	else if (keycode == S || keycode == S_MAC)
		cylinder->pos.z += 1;
	else if (keycode == Z || keycode == W_MAC)
		cylinder->pos.z -= 1;
	else if (keycode == UP || keycode == UP_MAC)
		cylinder->axis = vector_rot_x(cylinder->axis, 0.1);
	else if (keycode == DOWN || keycode == DOWN_MAC)
		cylinder->axis = vector_rot_x(cylinder->axis, -0.1);
	else if (keycode == LEFT || keycode == LEFT_MAC)
		cylinder->axis = vector_rot_y(cylinder->axis, 0.1);
	else if (keycode == RIGHT || keycode == RIGHT_MAC)
		cylinder->axis = vector_rot_y(cylinder->axis, -0.1);
	else if (keycode == A || keycode == Q_MAC)
		cylinder->axis = vector_rot_z(cylinder->axis, 0.1);
	else if (keycode == E || keycode == E_MAC)
		cylinder->axis = vector_rot_z(cylinder->axis, -0.1);
	else if (keycode == PLUS || keycode == PLUS_MAC)
		cylinder->r += 1;
	else if (keycode == MINUS || keycode == MINUS_MAC)
		cylinder->r -= 1;
	return (0);
}

int				key_hook_sphere(int keycode, t_sphere *sphere)
{
	if (keycode == D || keycode == D_MAC)
		sphere->pos.x += 1;
	else if (keycode == Q || keycode == A_MAC)
		sphere->pos.x -= 1;
	else if (keycode == SPACE || keycode == SPACE_MAC)
		sphere->pos.y += 1;
	else if (keycode == CONTROL || keycode == CONTROL_MAC)
		sphere->pos.y -= 1;
	else if (keycode == S || keycode == S_MAC)
		sphere->pos.z += 1;
	else if (keycode == Z || keycode == W_MAC)
		sphere->pos.z -= 1;
	else if (keycode == PLUS || keycode == PLUS_MAC)
		sphere->r += 1;
	else if (keycode == MINUS || keycode == MINUS_MAC)
		sphere->r -= 1;
	return (0);
}

int				key_hook_objects(int keycode, t_scene *scene)
{
	if (scene->selected_object)
	{
		if (scene->selected_object->type == SPHERE)
			key_hook_sphere(keycode, scene->selected_object->object);
		else if (scene->selected_object->type == PLANE)
			key_hook_plane(keycode, scene->selected_object->object);
		else if (scene->selected_object->type == CYLINDER)
			key_hook_cylinder(keycode, scene->selected_object->object);
	}
	return (0);
}
