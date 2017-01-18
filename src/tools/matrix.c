/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 01:20:22 by valentin          #+#    #+#             */
/*   Updated: 2017/01/18 16:52:21 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		vector_rot_x(t_vector v, float angle)
{
	t_vector	vector;

	vector.x = v.x;
	vector.y = v.y * cosf(angle) - v.z * sinf(angle);
	vector.z = v.y * sinf(angle) + v.z * cosf(angle);
	return (vector);
}

t_vector		vector_rot_y(t_vector v, float angle)
{
	t_vector	vector;

	vector.x = v.x * cosf(angle) + v.z * sinf(angle);
	vector.y = v.y;
	vector.z = -v.x * sinf(angle) + v.z * cosf(angle);
	return (vector);
}

t_vector		vector_rot_z(t_vector v, float angle)
{
	t_vector	vector;

	vector.x = v.x * cosf(angle) - v.y * sinf(angle);
	vector.y = v.x * sinf(angle) + v.y * cosf(angle);
	vector.z = v.z;
	return (vector);
}
