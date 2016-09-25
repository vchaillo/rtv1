#include "rtv1.h"

// t_color      ambient(t_light amb, t_hitpoint hitpoint)
// {
//   t_color    color;
//
//   color = hitpoint.diffuse_color;
//   if ((mult_color(hitpoint.ambient_color, amb.color)) > hitpoint.diffuse_color)
//     color = hitpoint.ambient_color;
//   else
//     color += color * amb.color;
//   return (color);
// }

t_color     spot(t_light spot, t_hitpoint hitpoint)
{
  t_color     color;
  t_vector    spot_dir;
  float       angle;

  // ray to the spot direction
  spot_dir.vx =  spot.pos.x - hitpoint.pos.x;
  spot_dir.vy =  spot.pos.y - hitpoint.pos.y;
  spot_dir.vz =  spot.pos.z - hitpoint.pos.z;

  // cacul de l'angle entre le rayon et la normale
  angle = dot_product(hitpoint.norm, normalize(spot_dir));
  // printf("angle : %f\n", angle);
  if (angle > 0)
    angle = 0;

  color = scalar_color(angle, mult_color(hitpoint.diffuse_color, spot.color));
  // printf("color : %d\n", color);
  return (color);
}

t_color     illuminate(t_env *e, t_ray *ray)
{
  t_color     color;

  //spot light
  color = scalar_color(0, ray->hitpoint.diffuse_color);
  color = add_color(spot(e->spot, ray->hitpoint), color);

  // ambient light
  // ray->hitpoint.ambient_color = WHITE;
  // color *= ambient(e->amb, ray->hitpoint);

  //directional light
  return (color);
}
