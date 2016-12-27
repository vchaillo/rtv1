/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:13 by vchaillo          #+#    #+#             */
/*   Updated: 2016/12/27 02:03:23 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int ac, char **av)
{
	t_env	e;

	if (ac > 1)
	{
		if (ft_strcmp(av[1], "-V") == 0 ||
		 ft_strcmp(av[1], "--minverbose") == 0)
			e.verbose = MIN_VERBOSE;
		else if (ft_strcmp(av[1], "-v") == 0 ||
		 ft_strcmp(av[1], "--verbose") == 0)
			e.verbose = FULL_VERBOSE;
		else
			print_error(ARG_ERROR);
	}
	start_mlx(&e);
	return (0);
}
