#include "rtv1.h"

float         hit_plan(t_env *e,t_ray *ray)
{
  float       t;
  t_plan      p;
  t_vector    rd;
  t_camera    ro;

  p = e->plan;
  rd = ray->d;
  ro = ray->o;
  t = -(p.a*ro.x + p.b*ro.y + p.c*ro.z + p.d);
  t /= (p.a*rd.vx + p.b*rd.vy + p.c*rd.vz);
  return (t);
}
