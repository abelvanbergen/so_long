/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_seperation_check.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 13:51:29 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:34:08 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "so_long.h"

static int	get_map_start(char *map, char c)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] != c)
			return (i);
		i++;
	}
	return (-1);
}

static int	get_map_end(char *map, char c)
{
	int	i;

	i = ft_strlen(map);
	while (i >= 0)
	{
		if (map[i] != c)
			return (i);
		i--;
	}
	return (-1);
}

bool	is_map_seperated(char *map)
{
	int	map_start;
	int	map_end;
	int	consecutive_newline;

	map_start = get_map_start(map, '\n');
	map_end = get_map_end(map, '\n');
	consecutive_newline = 0;
	while (map_start < map_end)
	{
		if (map[map_start] == '\n')
			consecutive_newline++;
		else
			consecutive_newline = 0;
		if (consecutive_newline == 2)
			return (true);
		map_start++;
	}
	return (false);
}
