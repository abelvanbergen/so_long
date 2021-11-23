/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 20:25:29 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/23 20:18:19 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include "so_long.h"

void	move_player(t_entity *player, t_mapinfo* mapinfo)
{
	char	d_loc;
	t_2int	p_pos;
	
	p_pos = player->pos;
	d_loc = mapinfo->map[p_pos.y + player->delta.y][p_pos.x + player->delta.x];
	if (d_loc == WALL_CHAR || (d_loc == EXIT_CHAR && mapinfo->tokens > 0))
		return ;
	if (d_loc == EXIT_CHAR && mapinfo->tokens == 0)
		exit(0); // mlx opruimen? en aparte geslaagde exit
	else if (d_loc == COLLECTIBLE_CHAR)
	{
		if (mapinfo->tokens != 0)
			mapinfo->tokens--;
		mapinfo->map[p_pos.y + player->delta.y][p_pos.x + player->delta.x] =
															COLLECTIBLE_CHAR;
	}
	else if (ft_strchr(ENEMY_CHARS, d_loc) != NULL)
		exit(1); //mlx opruimen? en aparte enemy failed exit
	player->pos.x += player->delta.x;
	player->pos.y += player->delta.y;
}

void	set_enemy_delta_for_crossing(t_entity *enemy, t_mapinfo* mapinfo)
{
	char	current_tile;
	char	delta_tile;
	t_2int	e_pos;
	t_2int	e_delta;
	
	e_pos = enemy->pos;
	e_delta = enemy->delta;
	delta_tile = mapinfo->map[e_pos.x + 2 * e_delta.x][e_pos.y + 2 * e_delta.y];
	if (delta_tile = )
}

void	move_enemy(t_entity *enemy, t_mapinfo* mapinfo)
{
	char	d_tile;
	char	c_tile;
	t_2int	e_pos;

	e_pos = enemy->pos;
	d_tile = mapinfo->map[e_pos.x + enemy->delta.x][e_pos.y + enemy->delta.y];
	c_tile = mapinfo->map[e_pos.x][e_pos.y];
	if (d_tile != c_tile)
	{
		if (c_tile == ENEMY_PATH_CROSSING)
			set_enemy_delta_for_crossing(enemy, mapinfo)
		else
		{
			enemy->delta.x *= -1;
			enemy->delta.y *= -1;
		}
		
	}
	else if (d_tile != c_tile)

	else
	{
		
	}
	
}

move_enemies(char **map, t_enemy *enemy)
{
	int	i;

	i = 0;
	while (i < enemy->amount)
	{
		
	}
}

// void	move(t_gamedata* gamedata, int dx, int dy)
// {
// 	// t_2int	pos;

// 	// pos.y = 0;
// 	// while (gamedata->map[pos.y] != NULL)
// 	// {
// 	// 	pos.x = 0;
// 	// 	while (gamedata->map[pos.y][pos.x] != '\0')
// 	// 	{
// 	// 		if (gamedata->map[pos.y][pos.x] == 'P')
// 	// 			move_player(t_gamedata* )
// 	// 		pos.x++;
// 	// 	}
// 	// 	pos.y++;
// 	// }
// }