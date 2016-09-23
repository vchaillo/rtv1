#include "rtv1.h"

t_vector   normalize(t_vector v)
{
  t_vector    norm;
  float       mag;

  mag = abs(sqrt((v.vx * v.vx) + (v.vy * v.vy) + (v.vz * v.vz)));
  if (mag)
  {
    norm.vx = v.vx / mag;
    norm.vy = v.vy / mag;
    norm.vz = v.vz / mag;
  }
  return (norm);
}

t_vector    vector_add(t_vector v1, t_vector v2)
{
  t_vector  sum;

  sum.vx = v1.vx + v2.vx;
  sum.vy = v1.vy + v2.vy;
  sum.vz = v1.vz + v2.vz;
  return (sum);
}

float     dot_product(t_vector v1, t_vector v2)
{
  float     product;

  product = v1.vx * v2.vx + v1.vy * v2.vy + v1.vz * v2.vz;
  return (product);
}
