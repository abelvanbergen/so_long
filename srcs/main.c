/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 19:25:54 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 21:07:25 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_game_data(t_gamedata* gamedata, char *filename)
{
	parse_map(filename, gamedata);
	gamedata->mlx.mlx = mlx_init();
	if (gamedata->mlx.mlx == NULL)
		exit_with_message("mlx_init failed", 1);
	get_window(&gamedata->mlx.window, gamedata->mlx.mlx, gamedata->map);
	get_image();
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