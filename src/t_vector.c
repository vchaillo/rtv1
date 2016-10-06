/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:25:07 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 16:12:51 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector        *new_vector(float x, float y, float z)
{
  t_vector      *vector;

  if (!(vector = (t_vector*)malloc(sizeof(t_vector))))
	  print_error(MALLOC_ERROR);
  vector->x = x;
  vector->y = y;
  vector->z = z;
  return (vector);
}

void			delete_vector(t_vector *vector)
{
	free(vector);
}
