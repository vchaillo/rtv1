/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:25:10 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/06 19:01:36 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		*normalize(t_vector *v)
{
	float		mag;

	mag = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	return (new_vector(v->x / mag, v->y / mag, v->z / mag));
}

t_vector		*vector_scalar(float scalar, t_vector *v)
{
	return (new_vector(scalar * v->x, scalar * v->y, scalar * v->z));
}

t_vector		*vector_add(t_vector *v1, t_vector *v2)
{
	return (new_vector(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z));
}

t_vector		*vector_sub(t_vector *v1, t_vector *v2)
{
	return (new_vector(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

float			dot_product(t_vector *v1, t_vector *v2)
{
	float		product;

	product = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (product);
}
