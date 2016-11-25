/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 03:48:41 by valentin          #+#    #+#             */
/*   Updated: 2016/11/25 01:49:12 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_hook(int keycode, t_env *e)
{
	if (e->verbose == TRUE)
	{
		ft_putstr("Keycode : ");
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	if (keycode == ESCAPE || keycode == ESCAPE_MAC)
	{
		if (e->scene)
			delete_scene(e->scene);
		exit(0);
	}
	else if (keycode == KP1 || keycode == KP1_MAC || keycode == NUM1_MAC)
	{
		if (e->scene->amb == ACTIVE)
			e->scene->amb = INACTIVE;
		else
			e->scene->amb = ACTIVE;
	}
	else if (keycode == KP2 || keycode == KP2_MAC || keycode == NUM2_MAC)
	{
		if (e->scene->diffuse == ACTIVE)
		e->scene->diffuse = INACTIVE;
		else
		e->scene->diffuse = ACTIVE;
	}
	else if (keycode == KP3 || keycode == KP3_MAC || keycode == NUM3_MAC)
	{
		if (e->scene->specular == ACTIVE)
		e->scene->specular = INACTIVE;
		else
		e->scene->specular = ACTIVE;
	}
	else if (keycode == KP4 || keycode == KP4_MAC || keycode == NUM4_MAC)
	{
		if (e->scene->spot == ACTIVE)
			e->scene->spot = INACTIVE;
		else
			e->scene->spot = ACTIVE;
	}
	else if (keycode == KP5 || keycode == KP5_MAC || keycode == NUM5_MAC)
	{
		if (e->scene->dir == ACTIVE)
			e->scene->dir = INACTIVE;
		else
			e->scene->dir = ACTIVE;
	}
	else if (keycode == D || keycode == D_MAC)
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
	else if (keycode == R || keycode == R_MAC)
		init_all(e);
	erase_image(e);
	return (0);
}
