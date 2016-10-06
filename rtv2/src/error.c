/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 16:01:11 by vchaillo          #+#    #+#             */
/*   Updated: 2016/10/04 16:31:32 by vchaillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_error(int error_code)
{
	if (error_code == MLX_ERROR)
		ft_putendl("Mlx initialization failed");
	else if (error_code == MALLOC_ERROR)
	{
		ft_putendl("Memory allocation failed");
		// delete_scene(e->scene);
	}
	exit (0);
}