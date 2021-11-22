/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 19:26:10 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 22:04:04 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define VALID_MAP_CHAR "10CEP"
# define PLAYER_CHAR 'P'
# define COLLECTIBLE_CHAR 'C'
# define EXIT_CHAR 'E'
# define WALL_CHAR '1'
# define ENEMY_CHARS "<>v^"

# define VIEW_ABLE_WITDH 15
# define VIEW_ABLE_HEIGHT 11
/*
** Must be a power of 2
*/
# define VIEW_ABLE_TEXTURE_SIZE 64

# define WALL_TEXTURE "textures/greystone.png"
# define PLAYER_TEXTURE "textures/player.png"
# define COLLECTIBLE_TEXTURE "textures/collectible.png"
# define BLOCKED_EXIT_TEXTURE "textures/blocked_exit.png"
# define UNBLOCKED_EXIT_TEXTURE "textures/unblocked_exit.png"
# define ENEMY_TEXTURE "textures/enemy.png"

#define W_KEY 13
#define S_KEY 1
#define A_KEY 0
#define D_KEY 2
#define LEFT_ARROW_KEY 126
#define LEFT_ARROW_KEY 125
#define LEFT_ARROW_KEY 123
#define RIGHT_ARROW_KEY 124

/*
** utils image elem
*/
typedef struct  	s_imginfo
{
    void			*img;
    char        	*addr;
    int         	bits_per_pixel;
    int         	line_length;
    int         	endian;
	int				img_width;
	int				img_height;
}					t_imginfo;

typedef struct	s_vla
{
	char		**array;
	int			size;
	int			capacity;
}				t_vla;

typedef	struct	s_2int
{
	int			x;
	int			y;
}				t_2int;

typedef struct		s_map_validation
{
	unsigned int	amount_players;
	unsigned int	amount_collectibles;
	unsigned int	amount_exit;
	unsigned int	map_len;
	bool			equal_map_len;
}					t_map_validation;

typedef struct 	s_window
{
	void		*frame;
	int			max_texture_size;
	t_2int		mapsize;
	char		**grid_to_show;
}				t_window;

typedef struct  s_mlx
{
	void		*mlx;
	t_window	window;
}               t_mlx;

typedef struct	s_textures
{
	t_imginfo	wall;
	t_imginfo	player;
	t_imginfo	collectible;
	t_imginfo	unblocked_exit;
	t_imginfo	blocked_exit;
	t_imginfo	enemy;
}				t_textures;

typedef struct	s_gamedata
{
	char		**map;
	t_textures	textures;
	t_mlx		mlx;
	t_imginfo	img;
	int			amount_collectible;
	t_2int		p_pos;
	char		p_pos_char;
}				t_gamedata;

void	exit_with_message(char *message, int exitcode);

int		get_exponent(int base, int power);
int		ft_arraylen(char **array);
void	print_map(char **array);
void	my_mlx_pixel_put(t_imginfo *img, int x, int y, int color);

void	vla_shrink(t_vla *vla);
void	vla_add_line_to_array(t_vla* vla, char *line);
void	vla_init(t_vla* vla);

void	map_validation(char **map, int* amount_collectibles);

void	parse_map(char *filename, t_gamedata *gamedata);
void	get_window(t_window* window, void* mlx, char **map);
void	get_textures(t_textures* textures, void *mlx);

#endif
