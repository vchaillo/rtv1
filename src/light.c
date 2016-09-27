#include "rtv1.h"

t_color     spot(t_env *e, t_light spot, t_hitpoint hitpoint)
{
  // t_ray       ray;
  (void)e;
  t_color     color;
  t_vector    spot_dir;
  float       cos_angle;

  // ray to the spot direction
  spot_dir.vx = spot.pos.x - hitpoint.pos.x;
  spot_dir.vy = spot.pos.y - hitpoint.pos.y;
  spot_dir.vz = spot.pos.z - hitpoint.pos.z;

  // ray.o = spot.pos;
  // ray.d = spot_dir;
  // ray.t = get_ray_intersection(e, &ray);

  // cacul de l'angle entre le rayon et la normale
  cos_angle = dot_product(hitpoint.norm, normalize(spot_dir));
  if (cos_angle < 0)
    cos_angle = 0;
  // printf("angle : %f\n", angle);
  color = scalar_color(cos_angle, mult_color(hitpoint.color, spot.color));
  return (color);
}

t_color     illuminate(t_env *e, t_ray *ray)
{
  t_color     color;

  ray->hitpoint.ambient = 0.06;
  ray->hitpoint.diffuse = 0.9;
  // ambient light
  color = scalar_color(ray->hitpoint.ambient, mult_color(e->amb.color, ray->hitpoint.color));

  //spot light
  color = add_color(scalar_color(ray->hitpoint.diffuse, spot(e, e->spot, ray->hitpoint)), color);
  color = add_color(scalar_color(ray->hitpoint.diffuse, spot(e, e->spot2, ray->hitpoint)), color);

  //directional light
  return (color);
}
