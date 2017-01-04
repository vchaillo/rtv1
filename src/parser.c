/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:31:16 by valentin          #+#    #+#             */
/*   Updated: 2017/01/04 16:33:21 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			parse_arguments(char **av, t_env *e)
{
	if (ft_strcmp(av[1], "-V") == 0 ||
	 ft_strcmp(av[1], "--minverbose") == 0)
		e->verbose = MIN_VERBOSE;
	else if (ft_strcmp(av[1], "-v") == 0 ||
	 ft_strcmp(av[1], "--verbose") == 0)
		e->verbose = FULL_VERBOSE;
	else
		print_error(ARG_ERROR);
}
