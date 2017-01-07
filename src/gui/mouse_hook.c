/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 03:48:37 by valentin          #+#    #+#             */
/*   Updated: 2017/01/07 02:42:45 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		mouse_hook(int button, int x, int y, t_env *e)
{
	print_mousehook(button, x, y, e);
	// erase_image(e);
	return (0);
}
