/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 17:35:44 by valentin          #+#    #+#             */
/*   Updated: 2016/12/23 16:34:32 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 			print_redraw_line(void)
{
	ft_putendl(TERM_BOLD_YELLOW);
	ft_putstr("======");
	ft_putstr(TERM_BOLD_GREY);
	ft_putstr(" RE DRAW ");
	ft_putstr(TERM_BOLD_YELLOW);
	ft_putendl("=======");
}

void			print_exposehook(t_env *e)
{
	if (e->verbose == TRUE)
	{
		ft_putendl(TERM_BOLD_RED);
		ft_putstr("Expose event detected !");
		ft_putendl(TERM_END);
	}
}

void			print_keyhook(int keycode, t_env *e)
{
	if (e->verbose)
	{
		print_redraw_line();
		ft_putstr(TERM_BOLD_GREY);
		ft_putstr("Keycode : ");
		ft_putstr(TERM_BOLD_GREEN);
		ft_putnbr(keycode);
		ft_putendl(TERM_END);
	}
}

void			print_mousehook(int button, int x, int y, t_env *e)
{
	if (e->verbose)
	{
		print_redraw_line();
		ft_putstr(TERM_BOLD_GREY);
		ft_putstr("Mouse button : ");
		ft_putstr(TERM_BOLD_GREEN);
		ft_putnbr(button);
		ft_putendl(TERM_BOLD_BLACK);
		ft_putstr("x : ");
		ft_putstr(TERM_BOLD_GREEN);
		ft_putnbr(x);
		ft_putstr(TERM_BOLD_BLACK);
		ft_putstr(", y : ");
		ft_putstr(TERM_BOLD_GREEN);
		ft_putnbr(y);
		ft_putendl(TERM_END);
	}
}
