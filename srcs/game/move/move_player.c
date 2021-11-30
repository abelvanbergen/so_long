/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:49:58 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:27:25 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

void	move_player(t_entity *player, t_bot *enemies, t_bot *pokemany,
															t_mapinfo *mapinfo)
{
	char	d_loc;
	t_2int	p_pos;

	p_pos = player->pos;
	d_loc = get_tile(p_pos.x + player->delta.x,
			p_pos.y + player->delta.y, mapinfo->map);
	if (d_loc == WALL_CHAR || (d_loc == EXIT_CHAR
			&& player->enemies_defeated != enemies->amount))
		return ;
	if (d_loc == EXIT_CHAR && player->enemies_defeated == enemies->amount)
		exit(0); // mlx opruimen? en aparte geslaagd exit
	is_next_pos_entity(enemies, player, player_moved_on_enemy);
	is_next_pos_entity(pokemany, player, player_try_catch_pokemon);
	if (d_loc == COLLECTIBLE_CHAR)
	{
		player->pokeballs++;
		mapinfo->map[p_pos.y + player->delta.y][p_pos.x + player->delta.x]
			= FLOOR_CHAR;
	}
	player->pos.x += player->delta.x;
	player->pos.y += player->delta.y;
}