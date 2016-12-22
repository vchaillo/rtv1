/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 15:15:39 by valentin          #+#    #+#             */
/*   Updated: 2016/12/22 17:45:17 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_camera_pos(t_env *e)
{
	ft_putendl(TERM_BOLD_GREY);
	ft_putendl("Camera position :");
	ft_putstr(TERM_BOLD_BLACK);
	ft_putstr("x : ");
	ft_putstr(TERM_BOLD_GREEN);
	ft_putnbr(e->scene->camera->pos.x);
	ft_putstr(TERM_BOLD_BLACK);
	ft_putstr(", y : ");
	ft_putstr(TERM_BOLD_GREEN);
	ft_putnbr(e->scene->camera->pos.y);
	ft_putstr(TERM_BOLD_BLACK);
	ft_putstr(", z : ");
	ft_putstr(TERM_BOLD_GREEN);
	ft_putnbr(e->scene->camera->pos.z);
	ft_putendl(TERM_END);
}

void 			print_nb_rays(t_env *e)
{
	ft_putendl(TERM_BOLD_GREY);
	ft_putendl("Rays informations :");
	ft_putstr(TERM_BOLD_BLACK);
	ft_putstr("Camera rays : ");
	ft_putstr(TERM_BOLD_GREEN);
	ft_putnbr(e->nb_cam_rays);
	ft_putendl(TERM_BOLD_BLACK);
	ft_putstr("Light rays : ");
	ft_putstr(TERM_BOLD_GREEN);
	ft_putnbr(e->nb_light_rays);
	ft_putendl(TERM_BOLD_BLACK);
	ft_putstr("Total rays : ");
	ft_putstr(TERM_BOLD_GREEN);
	ft_putnbr(e->nb_rays);
	ft_putendl(TERM_END);
}

void			print_objects(t_env *e)
{
	(void)e;
}

void			print_lights(t_env *e)
{
	(void)e;
}

void			print_cli_output(t_env *e)
{
	if (e->verbose)
	{
		print_nb_rays(e);
		print_camera_pos(e);
		// print_objects(e);
		// print_lights(e);
		ft_putstr(TERM_BOLD_BLACK);
		ft_putendl("======================");
	}
}
