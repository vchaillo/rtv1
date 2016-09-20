/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 21:23:00 by vchaillo          #+#    #+#             */
/*   Updated: 2016/05/19 21:58:08 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_all(t_env *e)
{
	e->background = BLACK;
	e->nb_rays = 0;

	e->camera.x = 0;
	e->camera.y = 0;
	e->camera.z = 10;

	e->screen.d = 1;
	e->screen.iar = (float)WIN_W / (float)WIN_H;
	e->screen.fov = tan((20 * 3.14) / 180);

	e->sphere.x = 0;
	e->sphere.y = 0;
	e->sphere.z = 0;
	e->sphere.r = 1;
	e->sphere.color = BLUE;

	e->plan.a = 1;
	e->plan.b = 0;
	e->plan.c = 0;
	e->plan.d = 0;
	e->plan.color = GREEN;
}
