/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 20:25:29 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/24 07:24:20 by abelfrancis   ########   odam.nl         */
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

void	turn(t_2int *delta, t_tile_sides direction)
{
	int	temp;

	if (direction == back)
	{
		delta->x *= -1;
		delta->y *= -1;
	}
	else if (direction == right)
	{
		temp = delta->x;
		delta->x = delta->y * -1;
		delta->y = temp;
	}
	else
	{
		temp = delta->x;
		delta->x = delta->y;
		delta->y = temp * -1;
	}
}

char*	set_sides(t_entity *enemy, t_mapinfo* mapinfo)
{
	t_2int	e_pos;
	t_2int	e_delta;
	char	tiles[4];

	e_pos = enemy->pos;
	e_delta = enemy->delta;
	tiles[front] = mapinfo->map[e_pos.x + e_delta.x][e_pos.y + e_delta.y];
	tiles[back] = mapinfo->map[e_pos.x - e_delta.x][e_pos.y - e_delta.y];
	turn(&e_delta, right);
	tiles[right] = mapinfo->map[e_pos.x + e_delta.x][e_pos.y + e_delta.y];
	tiles[left] = mapinfo->map[e_pos.x - e_delta.x][e_pos.y - e_delta.y];
	return tiles;
}

void	set_enemy_delta_for_crossing(t_entity *enemy, t_mapinfo* mapinfo)
{
	char	tile[4];
	char	tile_neighbours;
	
	tile = set_sides(enemy, mapinfo);
	if (tile[back] == ENEMY_PATH_HORIZONTAL)
		tile_neighbours = ENEMY_PATH_VERTICAL;
	else
		tile_neighbours = ENEMY_PATH_HORIZONTAL;
	if (tile[front] == tile[back])
		return ;
	if ((tile[right] == tile_neighbours && tile[left] == tile_neighbours) ||
			(tile[right] != tile_neighbours && tile[left] != tile_neighbours))
		turn(&enemy->delta, back);
	else if (tile[right] == tile_neighbours)
		turn(&enemy->delta, right);
	else
		turn(&enemy->delta, right);
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
			set_enemy_delta_for_crossing(enemy, mapinfo);
		else
			turn(&enemy->delta, back);	
	}
	enemy->pos.x += enemy->delta.x;
	enemy->pos.y += enemy->delta.y;	
}

void	move_enemies(char **map, t_enemy *enemy)
{
	int	i;

	i = 0;
	while (i < enemy->amount)
	{
		move_enemy(&enemy->array[i], );
		i++;
	}
}