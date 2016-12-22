/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 20:07:24 by valentin          #+#    #+#             */
/*   Updated: 2016/12/22 20:08:20 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_color(t_color color)
{
	ft_putnbr(color.r);
	ft_putnbr(color.g);
	ft_putnbr(color.b);
}
