#include "rtv1.h"

t_sphere        *new_sphere(float x, float y, float z, float r)
{
  t_sphere      *sphere;

  if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
    exit (0);
  sphere->pos = new_vector(x, y, z);
  sphere->r = r;
  return (sphere);
}
