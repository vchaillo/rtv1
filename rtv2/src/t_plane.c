/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:51 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 12:24:52 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_plane        *new_plane(float x, float y, float z, float d)
{
  t_plane      *plane;

  if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
    exit (0);
  plane->normal = new_vector(x, y, z);
  plane->d = d;
  return (plane);
}
