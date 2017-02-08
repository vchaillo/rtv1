/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 21:14:58 by valentin          #+#    #+#             */
/*   Updated: 2016/12/24 00:47:29 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void 		ft_putendl_color(char const *str, char const *color)
{
	ft_putstr(color);
	ft_putstr(str);
	ft_putendl(TERM_END);
}
