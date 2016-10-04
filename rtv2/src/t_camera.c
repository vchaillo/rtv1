/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:26 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 12:24:27 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_camera        *new_camera(float x, float y, float z)
{
  t_camera      *camera;

  if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
    exit (0);
  camera->pos = new_vector(x, y, z);
  camera->ratio = RATIO;
  camera->fov = FOV;
  camera->focale = FOCALE;
  return (camera);
}
