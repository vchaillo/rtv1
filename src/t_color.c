/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:34 by vchaillo          #+#    #+#             */
/*   Updated: 2016/11/21 17:20:30 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color			*new_color(int color)
{
	t_color		*new_color;

	if (!(new_color = (t_color*)malloc(sizeof(t_color))))
		print_error(MALLOC_ERROR);
	new_color->b = (color % 256);
	color /= 256;
	new_color->g = (color % 256);
	color /= 256;
	new_color->r = color;
	return (limit_color(new_color));
}

void			delete_color(t_color *color)
{
	free(color);
}
