#include "rtv1.h"

t_scene        *new_scene(t_color background_color, t_camera *camera)
{
  t_scene      *scene;

  if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
    exit (0);
  scene->background_color = background_color;
  scene->camera = camera;
  scene->objects = NULL;
  scene->lights = NULL;
  return (scene);
}
