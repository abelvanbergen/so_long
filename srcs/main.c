/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 19:25:54 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/22 09:11:41 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	get_game_data(t_gamedata *gamedata, char *filename)
{
	parse_map(filename, gamedata);
	printf("Vorbij het parse\n");
	gamedata->mlx.mlx = mlx_init();
	if (gamedata->mlx.mlx == NULL)
		exit_with_message("mlx_init failed", 1);
	printf("Vorbij mlx_init\n");
	get_window(&gamedata->mlx.window, gamedata->mlx.mlx, gamedata->map);
	printf("Vorbij get_window\n");
	get_image(&gamedata->img, gamedata->mlx.mlx, gamedata->mlx.window.mapsize,
										gamedata->mlx.window.max_texture_size);
	printf("Vorbij get_image\n");
	get_textures(&gamedata->textures, gamedata->mlx.mlx);
}

int main(int ac, char **av)
{
	t_gamedata	gamedata;

	if (ac != 2)
		exit_with_message\
			("Not the right amount of arguments\nUse [./solong file_name]", 1);
	get_game_data(&gamedata, av[1]);
}