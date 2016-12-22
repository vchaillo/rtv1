/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:34:52 by valentin          #+#    #+#             */
/*   Updated: 2016/12/22 20:12:31 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_amb_light(t_env *e)
{
	ft_putstr("Ambient light -> intensity : ");
	ft_putnbr(e->scene->amb_intensity);
	ft_putstr(", color : ");
	print_color(e->scene->amb_color);
	ft_putendl(TERM_END);
}

void			print_dir_light(t_light *light)
{
	ft_putstr("Directional light -> intensity : ");
	ft_putnbr(light->intensity);
	ft_putstr(", color : ");
	print_color(light->color);
	ft_putstr(", direction : (");
	ft_putnbr(light->dir.x);
	ft_putstr(", ");
	ft_putnbr(light->dir.y);
	ft_putstr(", ");
	ft_putnbr(light->dir.z);
	ft_putstr(")");
}

void			print_spot_light(t_light *light)
{
	ft_putstr("Spot light -> intensity : ");
	ft_putnbr(light->intensity);
	ft_putstr(", color : ");
	print_color(light->color);
	ft_putstr(", position : (");
	ft_putnbr(light->pos.x);
	ft_putstr(", ");
	ft_putnbr(light->pos.y);
	ft_putstr(", ");
	ft_putnbr(light->pos.z);
	ft_putstr(")");
}

void			print_lights(t_env *e)
{
	t_light		*tmp;

	ft_putendl(TERM_BOLD_GREY);
	ft_putendl("Lights informations :");
	ft_putstr(TERM_BOLD_BLACK);
	print_amb_light(e);
	ft_putstr(TERM_BOLD_GREEN);
	ft_putnbr(e->scene->nb_lights);
	ft_putendl(" lights in scene");
	tmp = e->scene->lights;
	while (tmp != NULL)
	{
		ft_putstr(TERM_BOLD_BLACK);
		if (tmp->type == DIR)
			print_dir_light(tmp);
		else if (tmp->type == SPOT)
			print_spot_light(tmp);
		ft_putendl(TERM_END);
		tmp = tmp->next;
	}
}
