/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 12:24:13 by vchaillo          #+#    #+#             */
/*   Updated: 2017/01/04 20:00:44 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int ac, char **av)
{
	t_env	e;

	load_scene(SCENE_1, &e);
	if (ac > 1)
		parse_arguments(ac, av, &e);
	start_mlx(&e);
	return (0);
}
