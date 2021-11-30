/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_enemy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:49:56 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:05:26 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	get_path_by_delta(t_2int *delta, bool straight)
{
	if (straight == true)
	{
		if (delta->x == 0)
			return (ENEMY_PATH_VERTICAL);
		return (ENEMY_PATH_HORIZONTAL);
	}
	else
	{
		if (delta->x == 0)
			return (ENEMY_PATH_HORIZONTAL);
		return (ENEMY_PATH_VERTICAL);
	}
}

static bool	is_valid_next_path(char c, t_2int *delta, bool straight)
{
	if (c == '+')
		return (true);
	if (c == get_path_by_delta(delta, straight))
		return (true);
	return (false);
}

static void	set_enemy_delta_for_crossing(char *tile, t_entity *enemy)
{	
	if (is_valid_next_path(tile[front], &enemy->delta, true))
		return ;
	if (!(is_valid_next_path(tile[right], &enemy->delta, false)
			^ is_valid_next_path(tile[left], &enemy->delta, false)))
		turn(&enemy->delta, back);
	else if (is_valid_next_path(tile[right], &enemy->delta, false))
		turn(&enemy->delta, right);
	else
		turn(&enemy->delta, left);
}

static void	move_enemy(t_entity *cur_enemy, char **map, t_bot *enemies)
{
	char	tile[5];
	t_2int	e_pos;

	e_pos = cur_enemy->pos;
	set_sides(tile, cur_enemy, map);
	if (tile[current] == ENEMY_PATH_CROSSING)
		set_enemy_delta_for_crossing(tile, cur_enemy);
	else if (tile[front] != tile[current] && tile[front] != ENEMY_PATH_CROSSING)
		turn(&cur_enemy->delta, back);
	is_next_pos_entity(enemies, cur_enemy, turn_enemies_backwards);
	tile[front] = get_tile(cur_enemy->pos.x + cur_enemy->delta.x,
			cur_enemy->pos.y + cur_enemy->delta.y, map);
	if (is_valid_next_path(tile[front], &cur_enemy->delta, true))
	{
		cur_enemy->pos.x += cur_enemy->delta.x;
		cur_enemy->pos.y += cur_enemy->delta.y;
	}
}

void	move_enemies(char **map, t_bot *enemies, t_entity *player)
{
	int			i;
	t_entity	*enemy;

	i = 0;
	while (i < enemies->amount)
	{
		if (enemies->array[i].shown == true)
		{
			enemy = &enemies->array[i];
			move_enemy(enemy, map, enemies);
			if (enemy->pos.x == player->pos.x && enemy->pos.y == player->pos.y)
				player_moved_on_enemy(player, enemy);
		}
		i++;
	}
}
