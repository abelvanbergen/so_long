/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   windowsetup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 13:54:12 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 17:20:43 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**get_grid_to_show(t_2int mapsize)
{
	int		i;
	char	**grid;

	grid = (char**)malloc(sizeof(char*) * (mapsize.y + 1));
	if (grid == NULL)
		exit_with_message("malloc failed", 1);
	i = 0;
	while (i < mapsize.y)
	{
		grid[i] = (char*)malloc(sizeof(char) * (mapsize.x + 1));
		if (grid[i] == NULL)
			exit_with_message("malloc failed", 1);
		i++;
	}
	return (grid);
}

int	*get_tilesizes(int begin_size)
{
	int	*array;
	int	i;

	array = (int*)malloc(sizeof(int) * get_exponent(2, begin_size));
	if (array == NULL)
		exit_with_message("malloc failed", 1);
	i = 0;
	while (begin_size != 1)
	{
		array[i] = begin_size;
		begin_size /= 2;
	}
	return (array);
}

void	get_window_size(t_window* window, void *mlx, char **map)
{
	t_2int	mapsize;
	t_2int	max_frame_size;
	int		*tilesizes;
	int		i;
	
	mapsize.x = ft_strlen(map[0]);
	mapsize.y = ft_arraylen(map);
	// mlx_get_screen_size(mlx, &max_frame_size.x, &max_frame_size.y);
	max_frame_size.x = 1920;
	max_frame_size.y = 1080;
	(void)mlx;
	if (mapsize.x < VIEW_ABLE_WITDH)
		window->mapsize.x = mapsize.x;
	else
		window->mapsize.x = VIEW_ABLE_WITDH;
	if (mapsize.y < VIEW_ABLE_HEIGHT)
		window->mapsize.y = mapsize.y;
	else
		window->mapsize.y = VIEW_ABLE_HEIGHT;
	tilesizes = get_tilesizes(VIEW_ABLE_TEXTURE_SIZE);
	i = 0;
	while (max_frame_size.x >= tilesizes[i] * window->mapsize.x && max_frame_size.y >= tilesizes[i] * window->mapsize.y)
		i++;
	window->max_texture_size = tilesizes[i];
}

void	get_window(t_window* window, void* mlx, char **map)
{
	t_2int	windowsize;
	get_window_size(window, mlx, map);
	windowsize.x = window->mapsize.x * window->max_texture_size;
	windowsize.y = window->mapsize.y * window->max_texture_size;
	window->frame = mlx_new_window(mlx, windowsize.x, windowsize.y, "so_long");
	if (window->frame == NULL)
		exit_with_message("mlx_new_window failed", 1);
	window->grid_to_show = get_grid_to_show(window->mapsize);
}