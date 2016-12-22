/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 22:41:26 by vchaillo          #+#    #+#             */
/*   Updated: 2016/12/12 21:25:03 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				is_in_shadow(t_object *objects, t_ray *ray)
{
	float		t;
	t_object	*object;

	object = objects;
	while (object != NULL)
	{
		if (object->type == SPHERE)
			t = hit_sphere((t_sphere *)object->object, ray);
		else if (object->type == PLANE)
			t = hit_plane((t_plane *)object->object, ray);
		else if (object->type == CYLINDER)
			t = hit_cylinder((t_cylinder *)object->object, ray);

		if (t > EPSILON && t < ray->t)
			return (TRUE);
		object = object->next;
	}
	return (FALSE);
}

t_color			specular(t_ray *v_ray, t_light *spot, t_ray *l_ray)
{
	t_color		color;
	t_ray		r_ray;
	float		cos_angle;
	float		spe;
	float		dot;

	cos_angle = 2 * dot_product(v_ray->hitpoint.normal, l_ray->d);
	r_ray.d = vector_sub(vector_scalar(cos_angle, v_ray->hitpoint.normal), l_ray->d);
	r_ray.d = normalize(r_ray.d);
	dot = dot_product(r_ray.d, v_ray->d);
	if (dot > 0)
		dot = 0;
	spe = pow(dot, v_ray->hitpoint.object->material);
	// spe *= 2;
	color = scalar_color(spe, spot->color);
	return (color);
}

t_color			diffuse(t_hitpoint hitpoint, t_light *spot, t_ray *ray)
{
	t_color		color;
	float		cos_angle;

	cos_angle = dot_product(hitpoint.normal, ray->d);
	if (cos_angle < 0)
		cos_angle = 0;
	color = scalar_color(cos_angle, mult_color(hitpoint.color, spot->color));
	return (color);
}

t_color			phong(t_env *e, t_light *spot, t_ray *v_ray)
{
	t_color		color;
	t_ray		l_ray;

	color = new_color(BLACK);
	l_ray.o = v_ray->hitpoint.pos;
	if (spot->type == SPOT)
	{
		l_ray.d = vector_sub(spot->pos, v_ray->hitpoint.pos);
		l_ray.t = sqrt((l_ray.d.x * l_ray.d.x) + (l_ray.d.y * l_ray.d.y) +
			(l_ray.d.z * l_ray.d.z));
	}
	else
	{
		l_ray.d = vector_scalar(-1, spot->dir);
		l_ray.t = 1000;
	}
	l_ray.d = normalize(l_ray.d);
	if (!(is_in_shadow(e->scene->objects, &l_ray)))
	{
		if (e->scene->diffuse == ACTIVE)
			color = add_color(diffuse(v_ray->hitpoint, spot, &l_ray), color);
		if (e->scene->specular == ACTIVE)
			color = add_color(specular(v_ray, spot, &l_ray), color);
	}
	return (color);
}

t_color			illuminate(t_env *e, t_ray *ray)
{
	t_color		color;
	t_light		*light;

	color = new_color(BLACK);
	light = e->scene->lights;
	while (light != NULL)
	{
		if (light->type == SPOT && e->scene->spot == ACTIVE)
			color = add_color(scalar_color(light->intensity,
				phong(e, light, ray)), color);
		else if (light->type == DIR && e->scene->dir == ACTIVE)
			color = add_color(scalar_color(light->intensity,
				phong(e, light, ray)), color);
		light = light->next;
		e->nb_light_rays++;
	}
	if (e->scene->amb == ACTIVE && (e->scene->spot || e->scene->dir))
		color = add_color(scalar_color((e->scene->amb_intensity / 10),
			mult_color(e->scene->amb_color, ray->hitpoint.color)), color);
	return (color);
}