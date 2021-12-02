/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 08:48:08 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/12/02 09:50:34 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "so_long.h"

static void	check_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len <= 4)
		exit_with_message("filename is incorrect\nUse [filename.ber]", 1);
	if (ft_strncmp(filename + len - 4, ".ber", 5) != 0)
		exit_with_message("filename is incorrect\nUse [filename.ber]", 1);
	return ;
}

char	*read_file(int fd, char *line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			exit_with_message("read failed", 1);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		line = malloc_check(ft_strjoin_and_free(line, buffer));
	}
	return (line);
}

static char	**read_map(char *filename)
{
	int		fd;
	char	*line;
	char	**array;

	check_filename(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_with_message("open failed", 1);
	line = read_file(fd, malloc_check(ft_strdup("")));
	if (line[0] == '\0')
		exit_with_message("File is empty", 1);
	if (is_map_seperated(line) == true)
		exit_with_message("There are newlines in the map", 1);
	array = malloc_check(ft_split(line, '\n'));
	free(line);
	return (array);
}

static void	set_floor_variation(char **map)
{
	int		index_to_place_flower;
	t_2int	loc;
	int		floor_index;

	loc.y = 0;
	floor_index = 0;
	while (map[loc.y] != NULL)
	{
		loc.x = 0;
		while (map[loc.y][loc.x] != '\0')
		{
			if (floor_index % DENSITIE_FLOOR_VAR == 0)
				index_to_place_flower = rand() % DENSITIE_FLOOR_VAR;
			if (map[loc.y][loc.x] == FLOOR_CHAR)
			{
				if (floor_index % DENSITIE_FLOOR_VAR == index_to_place_flower)
					map[loc.y][loc.x] = FLOOR_VARIATION_CHAR;
				floor_index++;
			}
			loc.x++;
		}
		loc.y++;
	}
}

void	parse_map(char *filename, t_gamedata *gamedata)
{
	t_map_validation	validation;

	gamedata->mapinfo.map = read_map(filename);
	gamedata->mapinfo.size.x = ft_strlen(gamedata->mapinfo.map[0]);
	gamedata->mapinfo.size.y = ft_arraylen(gamedata->mapinfo.map);
	map_validation(gamedata->mapinfo.map, &validation);
	gamedata->mapinfo.tokens = validation.amount_collectibles;
	gamedata->pokemany.amount = gamedata->mapinfo.tokens;
	gamedata->enemy.amount = validation.amount_enemy;
	set_entities(gamedata, validation.amount_pokemon_spawn);
	set_floor_variation(gamedata->mapinfo.map);
}
