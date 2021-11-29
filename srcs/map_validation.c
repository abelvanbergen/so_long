/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:30:40 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/29 11:54:38 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include "so_long.h"

void	check_if_map_is_closed(char **map)
{
	int j;
	int	last_line;
	int	last_char;

	j = 0;
	last_line = ft_arraylen(map) - 1;
	last_char = ft_strlen(map[0]) - 1;
	if (last_line < 2 || last_char < 2)
		exit_with_message("Map must be at least 3x3", 1);
	while (map[j] != NULL)
	{
		if (j != 0 && j != last_line)
		{
			if (map[j][0] != WALL_CHAR || map[j][last_char] != WALL_CHAR)
				exit_with_message("Map is not surrounded by walls", 1);
		}
		else if (str_is_only_char(map[j], WALL_CHAR) == 1)
			exit_with_message("Map is not surrounded by walls", 1);
		j++;
	}
}

void	get_map_validation_info(t_map_validation* info, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j] != NULL)
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (ft_strchr(VALID_MAP_CHAR, map[j][i]) == NULL)
				exit_with_message("Invalid character in map", 1);
			if (map[j][i] == PLAYER_CHAR)
				info->amount_players++;
			else if (map[j][i] == COLLECTIBLE_CHAR)
				info->amount_collectibles++;
			else if (map[j][i] == EXIT_CHAR)
				info->amount_exit++;
			else if (ft_strchr(ENEMY_CHARS, map[j][i]) != NULL)
				info->amount_enemy++;
			else if (map[j][i] == FLOOR_CHAR)
				info->amount_floor++;
			else if (ft_strchr(POKEMON_WALK_CHARS, map[j][i]) != NULL)
				info->amount_pokemon_spawn++;
			i++;
		}
		if (ft_strlen(map[j]) != info->map_len)
			info->equal_map_len = false;
		j++;
	}
}

void	map_validation(char **map, t_map_validation *validation)
{
	ft_bzero(validation, sizeof(t_map_validation));
	validation->map_len = ft_strlen(map[0]);
	validation->equal_map_len = true;
	get_map_validation_info(validation, map);
	if (validation->amount_players != 1)
		exit_with_message("Not the right amount of players\nCan only be 1", 1);
	if (validation->amount_collectibles <= 0)
		exit_with_message("Not enough collectibles\nShould be atleast 1", 1);
	if (validation->amount_exit <= 0)
		exit_with_message("Not enough exits\nShould be atleast 1", 1);
	if (validation->equal_map_len == false)
		exit_with_message("Map is not a rectangle", 1);
	if (validation->amount_enemy > validation->amount_collectibles)
		exit_with_message(
				"Map is unable to beat\nMore enemies than collectibles",1);
	if (validation->amount_collectibles > validation->amount_pokemon_spawn)
		exit_with_message(
			"Map is unable to beat\nNot enought places to spawn pokemon",1);
	check_if_map_is_closed(map);
}