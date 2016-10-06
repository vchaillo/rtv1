/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:51 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 20:04:17 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_plane        *new_plane(float x, float y, float z, float offset)
{
  t_plane      *plane;

  if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
	  print_error(MALLOC_ERROR);
  plane->normal = new_vector(x, y, z);
  plane->offset = offset;
  return (plane);
}


void			delete_plane(t_plane *plane)
{
	delete_vector(plane->normal);
	free(plane);
}
