/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 08:48:08 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/29 15:19:25 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "so_long.h"

void	set_entity(t_entity *dest, t_2int pos, int texture_id)
{
	ft_bzero(dest, sizeof(t_entity));
	dest->pos.x = pos.x;
	dest->pos.y = pos.y;
	dest->delta.x = 0;
	dest->delta.y = 1;
	dest->texture_id = texture_id;
	dest->pokeballs = 0;
	dest->pokemon = texture_id;
	dest->shown = true;
	dest->moved = true;
}

char	set_enemy(t_entity *enemy, char sort, t_2int pos)
{
	char new_tile;

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
		return(ENEMY_PATH_VERTICAL);
	}
	else if (sort == ENEMY_CHAR_LEFT)
	{
		enemy->delta.x = -1;
		return(ENEMY_PATH_HORIZONTAL);
	}
	else
	{
		enemy->delta.x = 1;
		return(ENEMY_PATH_HORIZONTAL);
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

int	get_map_start(char *map, char c)
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

int		get_map_end(char *map, char c)
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

char	**read_map(char *filename)
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*line;

	check_filename(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_with_message("open failed", 1);
	line = malloc_check(ft_strdup(""));
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
	if (line[0] == '\0')
		exit_with_message("File is empty", 1);
	if (is_map_seperated(line) == true)
		exit_with_message("There are newlines in the map", 1);
	return (malloc_check(ft_split(line, '\n')));
}

void	set_floor_variation(char **map)
{
	int		index_to_place_flower;
	t_2int			loc;
	int				floor_index;

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

void	set_pokemany(t_bot *pokemany, int pokemon_spawn, char **map)
{
	t_2int		loc;
	const int	step = pokemon_spawn / pokemany->amount;
	int			pokemon_index;
	int			spawn_index;
	int			index_to_place_pokemon;

	pokemon_index = 0;
	spawn_index = 0;
	loc.y = 0;
	while (map[loc.y] != NULL)
	{
		loc.x = 0;
		while (map[loc.y][loc.x] != '\0')
		{
			if (ft_strchr(POKEMON_WALK_CHARS, map[loc.y][loc.x]) != NULL)
			{
				if (spawn_index % step == 0)
					index_to_place_pokemon = rand() % step;
				if (spawn_index % step == index_to_place_pokemon)
				{
					set_entity(&pokemany->array[pokemon_index], loc,
												rand() % DIFFERENT_POKEMON);
					pokemany->array[pokemon_index].delta.y = 1;
					pokemany->array[pokemon_index].moved = false;
					pokemon_index++;
				}
				spawn_index++;
			}
			loc.x++;
		}
		loc.y++;
	}
}

void	set_entities(t_gamedata *gamedata, int amount_pokemon_spawn)
{
	gamedata->enemy.array = malloc(sizeof(t_entity) * gamedata->enemy.amount);
	if (gamedata->enemy.array == NULL)
		exit_with_message("malloc failed", 1);
	gamedata->pokemany.array = malloc(sizeof(t_entity) * gamedata->pokemany.amount);
	if (gamedata->pokemany.array == NULL)
		exit_with_message("malloc failed", 1);
	set_player_and_enemies(&gamedata->player, &gamedata->enemy, gamedata->mapinfo.map);
	set_pokemany(&gamedata->pokemany, amount_pokemon_spawn, gamedata->mapinfo.map);
}

void	parse_map(char *filename, t_gamedata *gamedata)
{
	t_map_validation	validation;
	
	gamedata->move_counter = 0;
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