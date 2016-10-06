#include "rtv1.h"

t_color			*spot_dir(t_object *objects, t_light *spot, t_hitpoint hitpoint)
{
	t_color		*color;
	t_vector	*spot_dir;
	// t_ray		ray;
	float		cos_angle;
	// float		dist_max;

	(void)objects;

	if (spot->dir == NULL)
		spot_dir = vector_sub(spot->pos, hitpoint.pos);
	else
		spot_dir = spot->dir;

	cos_angle = dot_product(hitpoint.normal, normalize(spot_dir));
	if (cos_angle < 0)
		cos_angle = 0;
	color = scalar_color(cos_angle, mult_color(hitpoint.color, spot->color));
	return (color);
}

t_color			*illuminate(t_scene *scene, t_hitpoint hitpoint)
{
	t_color		*color;
	t_light		*light;

	color = new_color(0);

	light = scene->lights;
	while (light != NULL)
	{
		if (light->type == AMB && scene->amb == ACTIVE)
			color = add_color(scalar_color(0.06, mult_color(light->color, hitpoint.color)), color);
		else if (light->type == SPOT && scene->spot == ACTIVE)
			color = add_color(scalar_color(0.9, spot_dir(scene->objects, light, hitpoint)), color);
		else if (light->type == DIR && scene->dir == ACTIVE)
			color = add_color(scalar_color(0.9, spot_dir(scene->objects, light, hitpoint)), color);
		light = light->next;
	}
	return (color);
}
