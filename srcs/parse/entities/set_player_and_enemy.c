/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_player_and_enemy.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:26:23 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/12/02 11:03:23 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

static char	set_enemy(t_entity *enemy, char sort, t_2int pos)
{
	char	new_tile;

	set_entity(enemy, pos, rand() % DIFFERENT_ENEMIES);
	ft_bzero(&enemy->delta, sizeof(t_2int));
	if (sort == ENEMY_CHAR_UP)
	{
		enemy->delta.y = -1;
		return (ENEMY_PATH_VERTICAL);
	}
	else if (sort == ENEMY_CHAR_DOWN)
	{
		enemy->delta.y = 1;
		return (ENEMY_PATH_VERTICAL);
	}
	else if (sort == ENEMY_CHAR_LEFT)
	{
		enemy->delta.x = -1;
		return (ENEMY_PATH_HORIZONTAL);
	}
	else
	{
		enemy->delta.x = 1;
		return (ENEMY_PATH_HORIZONTAL);
	}
	return (new_tile);
}

void	set_player_and_enemies(t_entity *player, t_bot *enemy, char **map)
{
	t_2int	pos;
	int		enemey_index;

	enemey_index = 0;
	pos.y = 0;
	while (map[pos.y] != NULL)
	{
		pos.x = 0;
		while (map[pos.y][pos.x] != '\0')
		{
			if (map[pos.y][pos.x] == PLAYER_CHAR)
			{
				set_entity(player, pos, 0);
				map[pos.y][pos.x] = FLOOR_CHAR;
			}
			else if (ft_strchr(ENEMY_CHARS, map[pos.y][pos.x]) != NULL)
			{
				map[pos.y][pos.x] = set_enemy(&enemy->array[enemey_index],
						map[pos.y][pos.x], pos);
				enemey_index++;
			}
			pos.x++;
		}
		pos.y++;
	}
}
