/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 08:48:08 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/27 16:15:51 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include "so_long.h"

void	set_entity(t_entity *dest, t_2int pos)
{
	dest->pos.x = pos.x;
	dest->pos.y = pos.y;
}

char	set_enemy(t_entity *enemy, char sort, t_2int pos)
{
	char new_tile;

	ft_bzero(&enemy->delta, sizeof(t_2int));
	if (sort == ENEMY_CHAR_UP)
	{
		new_tile = ENEMY_PATH_VERTICAL;
		enemy->delta.y = -1;
	}
	else if (sort == ENEMY_CHAR_DOWN)
	{
		new_tile = ENEMY_PATH_VERTICAL;
		enemy->delta.y = 1;
	}
	else if (sort == ENEMY_CHAR_LEFT)
	{
		new_tile = ENEMY_PATH_HORIZONTAL;
		enemy->delta.x = -1;
	}
	else
	{
		new_tile = ENEMY_PATH_HORIZONTAL;
		enemy->delta.x = 1;
	}
	set_entity(enemy, pos);
	printf("%d\n", DIFFERENT_ENEMIES);
	enemy->texture_id = rand() % DIFFERENT_ENEMIES;
	printf("set_texture_id: %d\n", enemy->texture_id);
	return (new_tile);
}

void	set_entities(t_entity *player, t_bot *enemy, char **map)
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
				set_entity(player, pos);
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

static char	**read_map(char *filename)
{
	int		fd;
	int		bytes_read;
	char	*line;
	t_vla	vla;

	check_filename(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_with_message("open failed", 1);
	vla_init(&vla);
	while (1)
	{
		bytes_read = get_next_line(fd, &line);
		if (bytes_read == -1)
			exit_with_message("Get_next_line failed", 1);
		if (line[0] == '\0' && bytes_read != 0)
			exit_with_message("Empty lines are not allowed", 1);
		if (line[0] != '\0')
			vla_add_line_to_array(&vla, line);
		if (bytes_read == 0)
			break ;
	}
	vla_shrink(&vla);
	close(fd);
	return vla.array;
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
					set_entity(&pokemany->array[pokemon_index], loc);
					pokemany->array[pokemon_index].texture_id = rand() % DIFFERENT_POKEMON;
					pokemany->array[pokemon_index].delta.x = 0;
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

void	parse_map(char *filename, t_gamedata *gamedata)
{
	t_map_validation	validation;
	
	srand((unsigned) time(0));
	gamedata->move_counter = 0;
	gamedata->mapinfo.map = read_map(filename);
	gamedata->mapinfo.size.x = ft_strlen(gamedata->mapinfo.map[0]);
	gamedata->mapinfo.size.y = ft_arraylen(gamedata->mapinfo.map);
	if (gamedata->mapinfo.size.y == 0)
		exit_with_message("file is empty", 1);
	map_validation(gamedata->mapinfo.map, &validation);
	gamedata->mapinfo.tokens = validation.amount_collectibles;
	gamedata->pokemany.amount = gamedata->mapinfo.tokens;
	gamedata->enemy.amount = validation.amount_enemy; 
	gamedata->enemy.array = malloc(sizeof(t_entity) * gamedata->enemy.amount);
	if (gamedata->enemy.array == NULL)
		exit_with_message("malloc failed", 1);
	gamedata->pokemany.array = malloc(sizeof(t_entity) * gamedata->pokemany.amount);
	if (gamedata->pokemany.array == NULL)
		exit_with_message("malloc failed", 1);
	set_entities(&gamedata->player, &gamedata->enemy, gamedata->mapinfo.map);
	printf("pokemon spwan places: %d\n", validation.amount_pokemon_spawn);
	set_pokemany(&gamedata->pokemany, validation.amount_pokemon_spawn, gamedata->mapinfo.map);
	for (int i = 0; i < gamedata->pokemany.amount; i++)
		printf("POKEMON-----\npos: %d-%d\nid: %d\n\n", gamedata->pokemany.array[i].pos.x, gamedata->pokemany.array[i].pos.y, gamedata->pokemany.array[i].texture_id);
	set_floor_variation(gamedata->mapinfo.map);
}