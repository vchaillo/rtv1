/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:13:55 by valentin          #+#    #+#             */
/*   Updated: 2016/12/23 16:32:30 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 			print_sphere(t_sphere *sphere)
{
	ft_putendl(" Sphere -> ");
	ft_putstr("   position : ");
	print_vector(sphere->pos);
	ft_putstr("\n   radius : ");
	ft_putnbr(sphere->r);
}

void 			print_plane(t_plane *plane)
{
	ft_putendl(" Plane ->");
	ft_putstr("   normal : ");
	print_vector(plane->normal);
	ft_putstr("\n   offset : ");
	ft_putnbr(plane->offset);
}

void 			print_cylinder(t_cylinder *cylinder)
{
	ft_putendl(" Cylinder ->");
	ft_putstr("   position : ");
	print_vector(cylinder->pos);
	ft_putstr("\n   axis : ");
	print_vector(cylinder->axis);
	ft_putstr("\n   radius : ");
	ft_putnbr(cylinder->r);
}

void			print_objects(t_env *e)
{
	t_object	*tmp;

	ft_putendl(TERM_BOLD_GREY);
	ft_putendl("Objects informations :");
	ft_putstr(TERM_BOLD_GREEN);
	ft_putnbr(e->scene->nb_objects);
	ft_putendl(" objects in scene");
	tmp = e->scene->objects;
	while (tmp != NULL)
	{
		ft_putstr(TERM_BOLD_BLACK);
		if (tmp->type == SPHERE)
			print_sphere((t_sphere *)tmp->object);
		else if (tmp->type == PLANE)
			print_plane((t_plane *)tmp->object);
		else if (tmp->type == CYLINDER)
			print_cylinder((t_cylinder *)tmp->object);
		ft_putendl(TERM_END);
		tmp = tmp->next;
	}
	(void)e;
}
