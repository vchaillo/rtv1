/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 01:20:22 by valentin          #+#    #+#             */
/*   Updated: 2017/01/07 02:11:45 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		matrix_rx(t_vector v, int angle)
{
	t_vector	vector;

	vector.x = v.x;
	vector.y = v.y * cos(angle) - v.z * sin(angle);
	vector.z = v.y * sin(angle) + v.z * cos(angle);
	return (vector);
}

t_vector		matrix_ry(t_vector v, int angle)
{
	t_vector	vector;

	vector.x = v.x * cos(angle) + v.z * sin(angle);
	vector.y = v.y;
	vector.z = v.x * sin(angle) - v.z * cos(angle);
	return (vector);
}

t_vector		matrix_rz(t_vector v, int angle)
{
	t_vector	vector;

	vector.x = v.x * cos(angle) - v.y * sin(angle);
	vector.y = v.x * sin(angle) + v.y * cos(angle);
	vector.z = v.z;
	return (vector);
}
