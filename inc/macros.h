/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:47:03 by valentin          #+#    #+#             */
/*   Updated: 2016/12/22 17:49:06 by valentinchaillou89###   ########.fr       */
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
** errors defines
*/
# define MALLOC_ERROR 0
# define MLX_ERROR 1

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

/*
** term colors defines
*/
# define TERM_BLACK "\033[30m"
# define TERM_RED "\033[31m"
# define TERM_GREEN "\033[32m"
# define TERM_YELLOW "\033[33m"
# define TERM_BLUE "\033[34m"
# define TERM_GREY "\033[37m"
# define TERM_END "\033[0;0m"

/*
** term bold colors defines
*/
# define TERM_BOLD_BLACK "\033[30;1m"
# define TERM_BOLD_RED "\033[31;1m"
# define TERM_BOLD_GREEN "\033[32;1m"
# define TERM_BOLD_YELLOW "\033[33;1m"
# define TERM_BOLD_BLUE "\033[34;1m"
# define TERM_BOLD_GREY "\033[37;1m"
/*
** term background colors defines
*/
# define TERM_BLACK_BG "\033[40m"
# define TERM_RED_BG "\033[41m"
# define TERM_GREEN_BG "\033[42m"
# define TERM_YELLOW_BG "\033[43m"
# define TERM_BLUE_BG "\033[44m"
# define TERM_GREY_BG "\033[45m"

#endif
