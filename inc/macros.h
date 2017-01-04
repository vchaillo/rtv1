/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:47:03 by valentin          #+#    #+#             */
/*   Updated: 2017/01/04 20:16:54 by valentinchaillou89###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** basics defines
*/
# define TRUE 1
# define FALSE 0
# define ACTIVE 1
# define INACTIVE 0

/*
** verbose defines
*/
# define FULL_VERBOSE 1
# define MIN_VERBOSE 2

/*
** errors defines
*/
# define MALLOC_ERROR 0
# define MLX_ERROR 1
# define ARG_ERROR 2

/*
** window and camera defines
*/
# define WIN_W 1080
# define WIN_H 720
# define RATIO (float)WIN_W / (float)WIN_H
# define FOV tan((20 * 3.14) / 180)
# define FOCALE 1
# define EPSILON 0.0001
# define MAX_DIST 1000

/*
** scenes defines
*/
# define SCENE_1 1
# define SCENE_2 2
# define SCENE_3 3

/*
** objects defines
*/
# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3

/*
** lights defines
*/
# define AMB 0
# define SPOT 1
# define DIR 2

#endif
