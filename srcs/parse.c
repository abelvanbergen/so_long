/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 08:48:08 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 15:22:12 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
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
	gamedata->map = read_map(filename);
	if (ft_arraylen(gamedata->map) == 0)
		exit_with_message("file is empty", 1);
	map_validation(gamedata->map);
}