/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 20:49:51 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/06 19:22:10 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			hit_plane(t_plane *plane, t_ray *ray)
{
	float		t;
	t_vector	*nor;
	t_vector	*ro;
	t_vector	*rd;

	nor = plane->normal;
	ro = ray->o;
	rd = ray->d;
	t = -(nor->x * ro->x + nor->y * ro->y + nor->z * ro->z + plane->offset);
	t /= (nor->x * rd->x + nor->y * rd->y + nor->z * rd->z);
	return (t);
}
