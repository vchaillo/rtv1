#include "rtv1.h"

int      amb(t_light amb, t_hitpoint hitpoint)
{
  int         color;

  color = hitpoint.diffuse_color;
  if ((hitpoint.diffuse_color * amb.color) > hitpoint.diffuse_color)
    color = hitpoint.diffuse_color;
  else
    color += color * amb.color;
  return (color);
}

int     spot(t_light spot, t_hitpoint hitpoint)
{
  int         color;
  t_vector    spot_dir;
  float       angle;

  // ray to the spot direction
  spot_dir.vx = hitpoint.pos.x - spot.pos.x;
  spot_dir.vy = hitpoint.pos.y - spot.pos.y;
  spot_dir.vz = hitpoint.pos.z - spot.pos.z;

  // cacul de l'angle entre le rayon et la normale
  angle = dot_product(normalize(hitpoint.norm), normalize(spot_dir));
  // printf("angle : %f\n", angle);
  // if (angle < 0)
  //   angle = 0;

  color = angle * hitpoint.diffuse_color * spot.color;
  // printf("color : %d\n", color);
  return (color);
}

int     illuminate(t_env *e, t_ray *ray)
{
  int         color;

  // ambient light no effect for now
  //spot light
  color = ray->hitpoint.diffuse_color;
  color += spot(e->spot, ray->hitpoint);
  color = amb(e->amb, ray->hitpoint);

  //directional light
  return (color);
}
