/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 14:34:08 by valentin          #+#    #+#             */
/*   Updated: 2016/12/23 15:00:06 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putfloat2(float f)
{
	float	dec_part;

	ft_putnbr(f);
	ft_putchar('.');
	dec_part = f - (int)f;
	ft_putnbr(dec_part * 100);
}
