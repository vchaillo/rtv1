#include "rtv1.h"

void   normalize(t_vector *v)
{
  float mag;

  mag = abs(sqrt((v->vx * v->vx) + (v->vy * v->vy) + (v->vz * v->vz)));
  if (mag)
  {
    v->vy /= mag;
    v->vx /= mag;
    v->vz /= mag;
  }
}
