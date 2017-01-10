/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 16:04:37 by valentin          #+#    #+#             */
/*   Updated: 2017/01/10 14:36:28 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cone			*new_cone(t_vector axis, t_vector apex, float aperture)
{
	t_cone	*cone;

	if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
		print_error(MALLOC_ERROR);
	cone->axis = axis;
	cone->apex = apex;
	cone->angle = aperture * (M_PI / 180);
	return (cone);
}

void			delete_cone(t_cone *cone)
{
	free(cone);
}
