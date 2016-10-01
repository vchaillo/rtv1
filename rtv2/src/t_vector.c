#include "rtv1.h"

t_vector        *new_vector(float x, float y, float z)
{
  t_vector      *vector;

  if (!(vector = (t_vector*)malloc(sizeof(t_vector))))
    exit (0);
  vector->x = x;
  vector->y = y;
  vector->z = z;
  return (vector);
}
