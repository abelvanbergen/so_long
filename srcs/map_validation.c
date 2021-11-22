/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:30:40 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/22 09:28:17 by avan-ber      ########   odam.nl         */
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
	while (map[j] != '\0')
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

	info->map_len = ft_strlen(map[0]);
	info->equal_map_len = true;
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
			i++;
		}
		if (ft_strlen(map[j]) != info->map_len)
			info->equal_map_len = false;
		j++;
	}
}

void	map_validation(char **map, int* amount_collectibles)
{
	t_map_validation	map_info;

	ft_bzero(&map_info, sizeof(t_map_validation));
	get_map_validation_info(&map_info, map);
	if (map_info.amount_players != 1)
		exit_with_message("Not the right amount of players\nCan only be 1", 1);
	if (map_info.amount_collectibles <= 0)
		exit_with_message("Not enough collectibles\nShould be atleast 1", 1);
	if (map_info.amount_players <= 0)
		exit_with_message("Not enough collectibles\nShould be atleast 1", 1);
	if (map_info.equal_map_len == false)
		exit_with_message("Map is not a rectyangle", 1);
	*amount_collectibles = map_info.amount_collectibles;
	check_if_map_is_closed(map);
}