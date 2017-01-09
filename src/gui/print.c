/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 05:46:34 by valentin          #+#    #+#             */
/*   Updated: 2017/01/09 17:46:29 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_gui_mode(t_env *e)
{
	if (e->scene->mode == EDIT_MODE)
		mlx_string_put(e->mlx, e->win, 10, 15, RED, "Edit mode");
	else
		mlx_string_put(e->mlx, e->win, 10, 15, RED, "Move mode");
}

void			print_gui_selected_object(t_env *e)
{
	int			x;
	int			y;

	x = 10;
	y = 35;
	if (e->scene->selected_object)
	{
		if (e->scene->selected_object->type == SPHERE)
			mlx_string_put(e->mlx, e->win, x, y, RED, "sphere selected");
		if (e->scene->selected_object->type == PLANE)
			mlx_string_put(e->mlx, e->win, x, y, RED, "plane selected");
		if (e->scene->selected_object->type == CYLINDER)
			mlx_string_put(e->mlx, e->win, x, y, RED, "cylinder selected");
		if (e->scene->selected_object->type == CONE)
			mlx_string_put(e->mlx, e->win, x, y, RED, "cone selected");
	}
	else
		mlx_string_put(e->mlx, e->win, x, y, RED, "no object selected");
}

void 			print_gui_output(t_env *e)
{
	print_gui_selected_object(e);
	print_gui_mode(e);
}
