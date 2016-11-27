/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_equations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 16:07:17 by valentin          #+#    #+#             */
/*   Updated: 2016/11/26 16:07:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			solve_deg2(double a, double b, double c)
{
	float		delta;
	float		res;
	float		x1;
	float		x2;

	delta = (b * b) - (4 * a * c);
	if (delta > 0)
	{
		x1 = (-b - sqrt(delta)) / (2 * a);
		x2 = (-b + sqrt(delta)) / (2 * a);
		if (x1 < x2)
			res = x1;
		else
			res = x2;
	}
	else if (delta == 0)
		res = -b / (2 * a);
	else
		res = 0;
	return (res);
}
