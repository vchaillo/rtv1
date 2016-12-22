/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:13:55 by valentin          #+#    #+#             */
/*   Updated: 2016/12/22 18:53:26 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 			print_sphere(t_sphere *sphere)
{
	ft_putstr("Sphere   -> position : (");
	ft_putnbr(sphere->pos.x);
	ft_putstr(", ");
	ft_putnbr(sphere->pos.y);
	ft_putstr(", ");
	ft_putnbr(sphere->pos.z);
	ft_putstr("), radius : ");
	ft_putnbr(sphere->r);
}

void 			print_plane(t_plane *plane)
{
	ft_putstr("Plane    -> normal : (");
	ft_putnbr(plane->normal.x);
	ft_putstr(", ");
	ft_putnbr(plane->normal.y);
	ft_putstr(", ");
	ft_putnbr(plane->normal.z);
	ft_putstr("), offset : ");
	ft_putnbr(plane->offset);
}

void 			print_cylinder(t_cylinder *cylinder)
{
	ft_putstr("Cylinder -> position : (");
	ft_putnbr(cylinder->pos.x);
	ft_putstr(", ");
	ft_putnbr(cylinder->pos.y);
	ft_putstr(", ");
	ft_putnbr(cylinder->pos.z);
	ft_putstr("), axis : (");
	ft_putnbr(cylinder->axis.x);
	ft_putstr(", ");
	ft_putnbr(cylinder->axis.y);
	ft_putstr(", ");
	ft_putnbr(cylinder->axis.z);
	ft_putstr("), radius : ");
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
