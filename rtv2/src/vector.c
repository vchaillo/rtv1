/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:25:10 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 12:25:11 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector    *normalize(t_vector v)
{
  float       mag;

  mag = fabs(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
  return (new_vector(v.x / mag, v.z / mag, v.z / mag));
}

t_vector    *vector_add(t_vector v1, t_vector v2)
{
  return (new_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

float       dot_product(t_vector v1, t_vector v2)
{
  float     product;

  product = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  return (product);
}
