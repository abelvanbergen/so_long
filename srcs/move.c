/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 20:25:29 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/24 14:07:28 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include "so_long.h"

char	get_tile(int x, int y, char **map)
{
	return (map[y][x]);
}

void	move_player(t_entity *player, t_mapinfo* mapinfo)
{
	char	d_loc;
	t_2int	p_pos;
	
	printf("start move_player\n");
	printf("delta: %d/%d\n", player->delta.x, player->delta.y);
	p_pos = player->pos;
	d_loc = get_tile(p_pos.x + player->delta.x, p_pos.y + player->delta.y, mapinfo->map);
	if (d_loc == WALL_CHAR || (d_loc == EXIT_CHAR && mapinfo->tokens > 0))
		return ;
	if (d_loc == EXIT_CHAR && mapinfo->tokens == 0)
		exit(0); // mlx opruimen? en aparte geslaagde exit
	//checken of ie niet tegen een enemy aan loopt, ook andersom nog maken
	else if (d_loc == COLLECTIBLE_CHAR)
	{
		if (mapinfo->tokens != 0)
			mapinfo->tokens--;
		mapinfo->map[p_pos.y + player->delta.y][p_pos.x + player->delta.x] =
															FLOOR_CHAR;
	}
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

char*	set_sides(char *tiles, t_entity *enemy, char **map)
{
	t_2int	e_pos;
	t_2int	e_delta;

	e_pos = enemy->pos;
	e_delta = enemy->delta;
	//hier zit de fout, hoe weet je welek deri front is
	tiles[current] = get_tile(e_pos.x, e_pos.y, map);
	tiles[front] = get_tile(e_pos.x + e_delta.x, e_pos.y + e_delta.y, map);
	tiles[back] = get_tile(e_pos.x - e_delta.x, e_pos.y - e_delta.y, map);
	turn(&e_delta, right);
	tiles[right] = get_tile(e_pos.x + e_delta.x, e_pos.y + e_delta.y, map);
	tiles[left] = get_tile(e_pos.x - e_delta.x, e_pos.y - e_delta.y, map);
	return tiles;
}

void	set_enemy_delta_for_crossing(char *tile, t_entity *enemy)
{
	char	tile_neighbours;
	
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
		turn(&enemy->delta, left);
}

void	move_enemy(t_entity *enemy, char **map)
{
	char	tile[5];
	t_2int	e_pos;

	e_pos = enemy->pos;
	set_sides(tile, enemy, map);
	if (tile[front] != tile[current])
	{
		if (tile[current] == ENEMY_PATH_CROSSING)
			set_enemy_delta_for_crossing(tile, enemy);
		else if (tile[front] != ENEMY_PATH_CROSSING)
			turn(&enemy->delta, back);	
	}
	tile[front] = get_tile(enemy->pos.x + enemy->delta.x,
											enemy->pos.y + enemy->delta.y, map);
	if (tile[current] == ENEMY_PATH_CROSSING || tile[front] == tile[current] || tile[front] == ENEMY_PATH_CROSSING)
	{
		enemy->pos.x += enemy->delta.x;
		enemy->pos.y += enemy->delta.y;	
	}
}

void	move_enemies(char **map, t_enemy *enemy)
{
	int	i;

	i = 0;
	while (i < enemy->amount)
	{
		move_enemy(&enemy->array[i], map);
		i++;
	}
}