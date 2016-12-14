/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:26 by vchaillo          #+#    #+#             */
/*   Updated: 2016/11/24 06:23:26 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_camera		*new_camera(float x, float y, float z)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		print_error(MALLOC_ERROR);
	camera->pos = new_vector(x, y, z);
	camera->ratio = RATIO;
	camera->fov = FOV;
	camera->focale = FOCALE;
	return (camera);
}

void			delete_camera(t_camera *camera)
{
	free(camera);
}
