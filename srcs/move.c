/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 20:25:29 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/29 19:17:49 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include <stdbool.h>
#include <stdlib.h>
#include "so_long.h"

bool	is_face_to_face(t_entity *a, t_entity *b)
{
	return (a->delta.x + b->delta.x + 2 * a->delta.y + 2 * b->delta.y == 0);
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
	else if (direction == left)
	{
		temp = delta->x;
		delta->x = delta->y;
		delta->y = temp * -1;
	}
}
void	pokemon_moved_on_pokemon(t_entity *moved, t_entity *collided)
{
	(void)moved;
	(void)collided;
	return ;
}

void	turn_enemies_backwards(t_entity *moved, t_entity *collided)
{
	if (is_face_to_face(moved, collided))
		turn(&collided->delta, back);
	turn(&moved->delta, back);
}

void	player_try_catch_pokemon(t_entity *player, t_entity *pokemon)
{
	if (player->pokeballs == 0)
		exit(0); //pokemon defeat player
	player->pokeballs--;
	player->pokemon++;
	// pokemon->pos.x = 0;
	// pokemon->pos.y = 0;
	pokemon->shown = false;
	pokemon->moved = false;
	printf("Dit vind ie best wel lastig\n");
}

void	player_moved_on_enemy(t_entity *player, t_entity *enemy)
{
	if (player->pokemon == 0)
		exit(0); //enemy defeat player, moved against a enemy, how to exit?
	player->pokemon--;
	// enemy->pos.x = 0;
	// enemy->pos.y = 0;
	enemy->shown = false;
}

bool	is_next_pos_entity(t_bot *entities, t_entity *entity, void (*f)(t_entity *, t_entity *))
{
	int		i;
	t_2int	next_pos;

	i = 0;
	next_pos.x = entity->pos.x + entity->delta.x;
	next_pos.y = entity->pos.y + entity->delta.y;
	while (i < entities->amount)
	{
		if (next_pos.x == entities->array[i].pos.x &&
			next_pos.y == entities->array[i].pos.y)
		{
			(f)(entity, &entities->array[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

char	get_tile(int x, int y, char **map)
{
	return (map[y][x]);
}

void	move_player(t_entity *player, t_bot *enemies, t_bot *pokemany, t_mapinfo* mapinfo)
{
	char	d_loc;
	t_2int	p_pos;
	
	p_pos = player->pos;
	d_loc = get_tile(p_pos.x + player->delta.x, p_pos.y + player->delta.y, mapinfo->map);
	if (d_loc == WALL_CHAR || (d_loc == EXIT_CHAR && mapinfo->tokens > 0))
		return ;
	if (d_loc == EXIT_CHAR && mapinfo->tokens == 0)
		exit(0); // mlx opruimen? en aparte geslaagde exit
	is_next_pos_entity(enemies, player, player_moved_on_enemy);
	is_next_pos_entity(pokemany, player, player_try_catch_pokemon);
	if (d_loc == COLLECTIBLE_CHAR)
	{
		player->pokeballs++;
		mapinfo->map[p_pos.y + player->delta.y][p_pos.x + player->delta.x] =
															FLOOR_CHAR;
	}
	player->pos.x += player->delta.x;
	player->pos.y += player->delta.y;
}

char*	set_sides(char *tiles, t_entity *entity, char **map)
{
	t_2int	e_pos;
	t_2int	e_delta;

	e_pos = entity->pos;
	e_delta = entity->delta;
	tiles[current] = get_tile(e_pos.x, e_pos.y, map);
	tiles[front] = get_tile(e_pos.x + e_delta.x, e_pos.y + e_delta.y, map);
	tiles[back] = get_tile(e_pos.x - e_delta.x, e_pos.y - e_delta.y, map);
	turn(&e_delta, right);
	tiles[right] = get_tile(e_pos.x + e_delta.x, e_pos.y + e_delta.y, map);
	tiles[left] = get_tile(e_pos.x - e_delta.x, e_pos.y - e_delta.y, map);
	return tiles;
}

char	get_path_by_delta(t_2int *delta, bool straight)
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

bool	is_valid_next_path(char c, t_2int *delta, bool straight)
{
	if (c == '+')
		return (true);
	if (c == get_path_by_delta(delta, straight))
		return (true);
	return (false);
}

void	set_enemy_delta_for_crossing(char *tile, t_entity *enemy)
{	
	if (is_valid_next_path(tile[front], &enemy->delta, true))
		return ;
	if (!(is_valid_next_path(tile[right], &enemy->delta, false) ^
						is_valid_next_path(tile[left], &enemy->delta, false)))
		turn(&enemy->delta, back);
	else if (is_valid_next_path(tile[right], &enemy->delta, false))
		turn(&enemy->delta, right);
	else
		turn(&enemy->delta, left);
}

void	move_enemy(t_entity *cur_enemy, char **map, t_bot *enemies)
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
	int	i;
	t_entity	*enemy;

	i = 0;
	while (i < enemies->amount)
	{
		if (enemies->array[i].shown == true)
		{
			enemy = &enemies->array[i];
			move_enemy(enemy, map, enemies);
			if (enemy->pos.x == player->pos.x && enemy->pos.y == player->pos.y)
				exit(0); // enemy steps on player
		}
		i++;
	}
}

void	move_pokemon_away_from_player(char **map, t_entity *pokemon)
{
	char	tile[5];

	set_sides(tile, pokemon, map);
	if (tile[current] == tile[back])
		turn(&pokemon->delta, back);
	else if (tile[current] == tile[right])
		turn(&pokemon->delta, right);
	else
		turn(&pokemon->delta, left);
}

void	move_pokemon(t_entity *pokemon, t_gamedata *gamedata)
{
	char			tile[5];
	t_tile_sides	order;
	int				i;
	
	order = rand() % 5;
	set_sides(tile, pokemon, gamedata->mapinfo.map);
	i = 0;
	while (i < 5)
	{
		if (tile[current] == tile[(i + order) % 5])
		{
			turn(&pokemon->delta, (i + order) % 5);
			break ;
		}
		i++;
	}
	if (pokemon->pos.x + pokemon->delta.x == gamedata->player.pos.x && pokemon->pos.y + pokemon->delta.y == gamedata->player.pos.y)
		move_pokemon_away_from_player(gamedata->mapinfo.map, pokemon);
	tile[front] = get_tile(pokemon->pos.x + pokemon->delta.x, pokemon->pos.y + pokemon->delta.y, gamedata->mapinfo.map);
	if (tile[front] == tile[current] && !is_next_pos_entity(&gamedata->pokemany, pokemon, pokemon_moved_on_pokemon))
	{
		pokemon->pos.x += pokemon->delta.x;
		pokemon->pos.y += pokemon->delta.y;
		pokemon->moved = true;
	}
	else
		pokemon->moved = false;
}

void	move_pokemany(t_gamedata *gamedata, t_bot *pokemany)
{
	int			i;
	t_entity	*pokemon;

	i = 0;
	while (i < pokemany->amount)
	{
		printf("shown: %d\n", pokemany->array[i].shown);
		if (pokemany->array[i].shown == true)
		{
			pokemon = &pokemany->array[i];
			move_pokemon(pokemon, gamedata);
			i++;
		}
	}
}