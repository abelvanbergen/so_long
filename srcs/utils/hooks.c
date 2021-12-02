/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 18:57:12 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 13:23:42 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

int	close_screen(t_move *move)
{
	(void)move;
	exit(0);
}

int	key_press(int keycode, t_move *move)
{
	if (keycode == W_KEY || keycode == UP_ARROW_KEY)
		move->up = true;
	if (keycode == S_KEY || keycode == DOWN_ARROW_KEY)
		move->down = true;
	if (keycode == A_KEY || keycode == LEFT_ARROW_KEY)
		move->left = true;
	if (keycode == D_KEY || keycode == RIGHT_ARROW_KEY)
		move->right = true;
	if (keycode == ESC_KEY)
		close_screen(move);
	return (0);
}
