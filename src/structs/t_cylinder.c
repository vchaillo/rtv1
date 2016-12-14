/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 16:04:37 by valentin          #+#    #+#             */
/*   Updated: 2016/11/26 17:25:25 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cylinder		*new_cylinder(t_vector axis, t_vector pos, float r)
{
	t_cylinder	*cylinder;

	if (!(cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
		print_error(MALLOC_ERROR);
	cylinder->axis = axis;
	cylinder->pos = pos;
	cylinder->r = r;
	return (cylinder);
}

void			delete_cylinder(t_cylinder *cylinder)
{
	free(cylinder);
}
