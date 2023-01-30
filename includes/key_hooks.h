/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 03:37:47 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 10:06:46 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOKS_H
# define KEY_HOOKS_H

// https://www.toptal.com/developers/keycode
// https://docs.oracle.com/
//cd/E67482_01/oscar/pdf/45/OnlineHelp_45/helpOnPS2keyCodes.html

// PS2 keyboard Key code (Windows) oracle linux //
//---->My PC(PS2 keyboard) Key Codes<----//
# if defined(__APPLE__)
#  define FREE_MLX			0
#  define KEY_W				13
#  define KEY_A				0
#  define KEY_S				1
#  define KEY_D				2
#  define KEY_H				4
#  define KEY_R				15
#  define KEY_E				14
#  define KEY_M				46

#  define KEY_NUM_1			18
#  define KEY_NUM_2			19
#  define KEY_NUM_3			20
#  define KEY_NUM_4			21
#  define KEY_NUM_5			23
#  define KEY_NUM_6			22
#  define KEY_NUM_7			26
#  define KEY_NUM_8			28
#  define KEY_NUM_9			25
#  define KEY_NUM_0			29

#  define KEY_SPACE			49

#  define KEY_ESC			53

#  define KEY_ARROW_UP		126
#  define KEY_ARROW_DOWN	125
#  define KEY_ARROW_LEFT	123
#  define KEY_ARROW_RIGHT	124

#  define KEY_L_SHIFT		257

#  define GO_FORWARD		1
#  define GO_BACKWARD		2
#  define GO_LEFT			4
#  define GO_RIGHT			8
#  define TURN_UP			16
#  define TURN_DOWN			32
#  define TURN_LEFT			64
#  define TURN_RIGHT		128
# endif

// ---->AppleScript Key Codes<----//
# if defined(linux)
#  define FREE_MLX			1
#  define KEY_W				119
#  define KEY_A				97
#  define KEY_S				115
#  define KEY_D				100
#  define KEY_H				104
#  define KEY_R				114
#  define KEY_E				101
#  define KEY_M				109

#  define KEY_NUM_1			49
#  define KEY_NUM_2			50
#  define KEY_NUM_3			51
#  define KEY_NUM_4			52
#  define KEY_NUM_5			53
#  define KEY_NUM_6			54
#  define KEY_NUM_7			55
#  define KEY_NUM_8			56
#  define KEY_NUM_9			57
#  define KEY_NUM_0			48

#  define KEY_SPACE			32

#  define KEY_ESC			65307

#  define KEY_ARROW_UP		65362
#  define KEY_ARROW_DOWN	65364
#  define KEY_ARROW_LEFT	65361
#  define KEY_ARROW_RIGHT	65363

#  define KEY_L_SHIFT		65505

#  define GO_FORWARD		1
#  define GO_BACKWARD		2
#  define GO_LEFT			4
#  define GO_RIGHT			8
#  define TURN_UP			16
#  define TURN_DOWN			32
#  define TURN_LEFT			64
#  define TURN_RIGHT		128
# endif

#endif