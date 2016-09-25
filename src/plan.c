#include "rtv1.h"

float         hit_plan(t_env *e, t_ray *ray)
{
  float       t;
  t_vector    p_norm;
  t_vector    rd;
  t_point     ro;

  p_norm = e->plan.norm;
  rd = ray->d;
  ro = ray->o;
  t = -(p_norm.vx*ro.x + p_norm.vy*ro.y + p_norm.vz*ro.z + e->plan.d);
  t /= (p_norm.vx*rd.vx + p_norm.vy*rd.vy + p_norm.vz*rd.vz);
  if (t > 0)
  {
    ray->hitpoint.pos.x = ray->o.x + ray->d.vx * t;
    ray->hitpoint.pos.y = ray->o.y + ray->d.vy * t;
    ray->hitpoint.pos.z = ray->o.z + ray->d.vz * t;
    ray->hitpoint.norm.vx = p_norm.vx;
    ray->hitpoint.norm.vy = p_norm.vy;
    ray->hitpoint.norm.vz = p_norm.vz;
  }
  return (t);
}
