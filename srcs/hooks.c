/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 18:57:12 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/23 09:55:36 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		exit_with_message("Quited the game", 1); //juiste quit()
	return (0);
}