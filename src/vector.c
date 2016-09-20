#include "rtv1.h"

void   normalize(t_vector *v)
{
  float norm;

  norm = sqrt((v->vx * v->vx) + (v->vy * v->vy) + (v->vz * v->vz));
  if (norm)
  {
    v->vy /= norm;
    v->vx /= norm;
    v->vz /= norm;
  }
}

float   dot_product(t_vector *v1, t_vector *v2)
{
  return ((v1->vx * v2->vx) + (v1->vy * v2->vy) + (v1->vz * v2->vz));
}
