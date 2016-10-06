/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:23:10 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 12:24:02 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color     *limit_color(t_color *color)
{
  if (color->r > 255)
  color->r = 255;
  if (color->g > 255)
  color->g = 255;
  if (color->b > 255)
  color->b = 255;
  return (color);
}

t_color     *scalar_color(float scalar, t_color *color)
{
  color->r *= scalar;
  color->g *= scalar;
  color->b *= scalar;
  return (limit_color(color));
}

t_color     *add_color(t_color *color1, t_color *color2)
{
  t_color   *color;

  color = new_color(0);
  color->r = color1->r + color2->r;
  color->g = color1->g + color2->g;
  color->b = color1->b + color2->b;
  return (limit_color(color));
}

t_color     *mult_color(t_color *color1, t_color *color2)
{
  t_color   *color;

  color = new_color(0);
  color->r = color1->r * color2->r;
  color->g = color1->g * color2->g;
  color->b = color1->b * color2->b;
  return (limit_color(color));
}
