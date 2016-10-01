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
  return (t);
}
