/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 03:48:37 by valentin          #+#    #+#             */
/*   Updated: 2016/11/24 03:58:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		mouse_hook(int button, int x, int y, t_env *e)
{
	ft_putstr("Mouse button : ");
	ft_putnbr(button);
	ft_putstr(", x : ");
	ft_putnbr(x);
	ft_putstr(", y : ");
	ft_putnbr(y);
	ft_putchar('\n');
	erase_image(e);
	return (0);
}
