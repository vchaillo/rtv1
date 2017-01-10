/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:40:03 by vchaillo          #+#    #+#             */
/*   Updated: 2017/01/10 14:45:59 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				key_hook_cylinder_rotation_ae(int keycode, t_cylinder *cylinder)
{
	if (keycode == A || keycode == Q_MAC)
	{
		if (cylinder->axis != Z_AXIS)
			cylinder->axis = cylinder->axis == X_AXIS ? Y_AXIS : X_AXIS;
	}
	else if (keycode == E || keycode == E_MAC)
	{
		if (cylinder->axis != Z_AXIS)
			cylinder->axis = cylinder->axis == X_AXIS ? Y_AXIS : X_AXIS;
	}
	return (0);
}

int				key_hook_cylinder_rotation_udlr(int keycode, t_cylinder *cylinder)
{
	if (keycode == UP || keycode == UP_MAC)
	{
		if (cylinder->axis != X_AXIS)
			cylinder->axis = cylinder->axis == Y_AXIS ? Z_AXIS : Y_AXIS;
	}
	else if (keycode == DOWN || keycode == DOWN_MAC)
	{
		if (cylinder->axis != X_AXIS)
			cylinder->axis = cylinder->axis == Y_AXIS ? Z_AXIS : Y_AXIS;
	}
	else if (keycode == LEFT || keycode == LEFT_MAC)
	{
		if (cylinder->axis != Y_AXIS)
			cylinder->axis = cylinder->axis == Z_AXIS ? X_AXIS : Z_AXIS;
	}
	else if (keycode == RIGHT || keycode == RIGHT_MAC)
	{
		if (cylinder->axis != Y_AXIS)
			cylinder->axis = cylinder->axis == Z_AXIS ? X_AXIS : Z_AXIS;
	}
	else
	key_hook_cylinder_rotation_ae(keycode, cylinder);
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
	else if (keycode == PLUS || keycode == PLUS_MAC)
		cylinder->r += 1;
	else if (keycode == MINUS || keycode == MINUS_MAC)
		cylinder->r -= 1;
	else
		key_hook_cylinder_rotation_udlr(keycode, cylinder);
	return (0);
}
