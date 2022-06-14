/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_code.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoro <mgregoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:38:27 by mgregoro          #+#    #+#             */
/*   Updated: 2022/06/14 12:05:50 by mgregoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_CODE_H
# define KEY_CODE_H

# ifdef __linux__
#  define DOWN		65364
#  define UP		65362
#  define LEFT		65361
#  define RIGHT		65363

#  define W_UP		119
#  define S_DOWN 	115
#  define A_LEFT 	97
#  define D_RIGHT	100

#  define ESC 		65307
# else
#  define UP		126
#  define DOWN	    125
#  define LEFT	    123
#  define RIGHT	    124
#  define W_UP		13
#  define S_DOWN 	1
#  define A_LEFT 	0
#  define D_RIGHT	2

#  define ESC		53
# endif
#endif
