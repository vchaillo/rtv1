#include "rtv1.h"

t_color     scalar_color(float scalar, t_color color)
{
  color.r *= scalar;
  color.g *= scalar;
  color.b *= scalar;
  return (color);
}

t_color     add_color(t_color color1, t_color color2)
{
  t_color   color;

  color.r = color1.r + color2.r;
  color.g = color1.g + color2.g;
  color.b = color1.b + color2.b;
  return (color);
}

t_color     mult_color(t_color color1, t_color color2)
{
  t_color   color;

  color.r = color1.r * color2.r;
  color.g = color1.g * color2.g;
  color.b = color1.b * color2.b;
  return (color);
}

t_color     new_color(int color)
{
  t_color   new_color;

  new_color.b = (color % 256);
  color /= 256;
  new_color.g = (color % 256);
  color /= 256;
  new_color.r = (color % 256);
  return (new_color);
}
