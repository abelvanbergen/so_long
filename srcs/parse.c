/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 08:48:08 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/23 19:44:00 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
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
	return (new_tile);
}

void	set_entities(t_entity *player, t_enemy *enemy, char **map)
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

void	parse_map(char *filename, t_gamedata *gamedata)
{
	gamedata->mapinfo.map = read_map(filename);
	gamedata->mapinfo.size.x = ft_strlen(gamedata->mapinfo.map[0]);
	gamedata->mapinfo.size.y = ft_arraylen(gamedata->mapinfo.map);
	if (gamedata->mapinfo.size.y == 0)
		exit_with_message("file is empty", 1);
	map_validation(gamedata->mapinfo.map, &gamedata->mapinfo.tokens,
													&gamedata->enemy.amount);
	gamedata->enemy.array = malloc(sizeof(t_entity) * gamedata->enemy.amount);
	set_entities(&gamedata->player, &gamedata->enemy, gamedata->mapinfo.map);
	for(int i = 0; i < gamedata->enemy.amount; i++)
		printf("enemy %i:\npos %d/%d\ndelta %d/%d\n------\n", i, gamedata->enemy.array[i].pos.x, gamedata->enemy.array[i].pos.y, gamedata->enemy.array[i].delta.x, gamedata->enemy.array[i].delta.y);
}