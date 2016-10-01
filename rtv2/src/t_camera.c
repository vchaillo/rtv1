#include "rtv1.h"

t_camera        *new_camera(float x, float y, float z)
{
  t_camera      *camera;

  if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
    exit (0);
  camera->pos = new_vector(x, y, z);
  camera->ratio = RATIO;
  camera->fov = FOV;
  camera->focale = FOCALE;
  return (camera);
}
