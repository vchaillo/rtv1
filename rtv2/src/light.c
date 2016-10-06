#include "rtv1.h"

t_color			*spot(t_object *objects, t_light *spot, t_hitpoint hitpoint)
{
	t_color		*color;
	t_vector	*spot_dir;
	float		cos_angle;

	(void)objects;

	spot_dir = vector_sub(spot->pos, hitpoint.pos);

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
		if (light->type == AMB)
			color = add_color(scalar_color(0.06, mult_color(light->color, hitpoint.color)), color);
		else if (light->type == SPOT)
			color = add_color(spot(scene->objects, light, hitpoint), color);
		// else if (light->type == DIR)
		// 	printf("DIR\n");
		light = light->next;
	}

	// ray->hitpoint.ambient = 0.06;
	// ray->hitpoint.diffuse = 0.9;
	//
	// color = scalar_color(ray->hitpoint.ambient, mult_color(e->amb.color, ray->hitpoint.color));
	//
	// color = add_color(scalar_color(ray->hitpoint.diffuse, spot(e, e->spot, ray->hitpoint)), color);
	// color = add_color(scalar_color(ray->hitpoint.diffuse, spot(e, e->spot2, ray->hitpoint)), color);

	return (color);
}
