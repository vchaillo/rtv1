/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 03:48:41 by valentin          #+#    #+#             */
/*   Updated: 2016/12/23 16:39:22 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_hook_camera(int keycode, t_env *e)
{
	if (keycode == D || keycode == D_MAC)
		e->scene->camera->pos.x += 1;
	else if (keycode == Q || keycode == Q_MAC)
		e->scene->camera->pos.x -= 1;
	else if (keycode == SPACE || keycode == SPACE_MAC)
		e->scene->camera->pos.y += 1;
	else if (keycode == CONTROL || keycode == CONTROL_MAC)
		e->scene->camera->pos.y -= 1;
	else if (keycode == S || keycode == S_MAC)
		e->scene->camera->pos.z += 1;
	else if (keycode == Z || keycode == Z_MAC)
		e->scene->camera->pos.z -= 1;
	return (0);
}

int		key_hook_light(int keycode, t_env *e)
{
	if (keycode == KP1 || keycode == KP1_MAC || keycode == NUM1_MAC)
		e->scene->amb = (e->scene->amb == ACTIVE) ? INACTIVE : ACTIVE;
	else if (keycode == KP2 || keycode == KP2_MAC || keycode == NUM2_MAC)
		e->scene->diffuse = (e->scene->diffuse == ACTIVE) ? INACTIVE : ACTIVE;
	else if (keycode == KP3 || keycode == KP3_MAC || keycode == NUM3_MAC)
		e->scene->specular = (e->scene->specular == ACTIVE) ? INACTIVE : ACTIVE;
	else if (keycode == KP4 || keycode == KP4_MAC || keycode == NUM4_MAC)
		e->scene->spot = (e->scene->spot == ACTIVE) ? INACTIVE : ACTIVE;
	else if (keycode == KP5 || keycode == KP5_MAC || keycode == NUM5_MAC)
		e->scene->dir = (e->scene->dir == ACTIVE) ? INACTIVE : ACTIVE;
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	if (keycode == ESCAPE || keycode == ESCAPE_MAC)
	{
		if (e->scene)
			delete_scene(e->scene);
		exit(0);
	}
	else if (keycode == R || keycode == R_MAC)
		init_all(e);
	else
	{
		key_hook_camera(keycode, e);
		key_hook_light(keycode, e);
	}
	print_keyhook(keycode, e);
	erase_image(e);
	return (0);
}
