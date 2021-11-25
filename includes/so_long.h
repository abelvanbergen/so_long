/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 19:26:10 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/25 20:11:18 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define VALID_MAP_CHAR "10CEP<>^v-|+"
# define PLAYER_CHAR 'P'
# define COLLECTIBLE_CHAR 'C'
# define EXIT_CHAR 'E'
# define WALL_CHAR '1'
# define SHRUB_CHAR 'S'
# define FLOOR_CHAR '0'
# define ENEMY_CHAR_UP '^'
# define ENEMY_CHAR_DOWN 'v'
# define ENEMY_CHAR_LEFT '<'
# define ENEMY_CHAR_RIGHT '>'
# define ENEMY_PATH_VERTICAL '|'
# define ENEMY_PATH_HORIZONTAL '-'
# define ENEMY_PATH_CROSSING '+'
# define ENEMY_CHARS "<>^v"
# define FLOOR_VARIATION_CHAR '2'

/*
** Must be odd numbers, so that the player can stand in the middle
*/
# define VIEWABLE_WITDH 20
# define VIEWABLE_HEIGHT 14
/*
** Must be a power of 2
*/
# define VIEWABLE_TEXTURE_SIZE 128

# define WALL_TEXTURE "textures/pokebal/stone.xpm"
# define PLAYER_TEXTURE "textures/pokebal/pikachu.xpm"
# define COLLECTIBLE_TEXTURE "textures/pokebal/ball.xpm"
# define BLOCKED_EXIT_TEXTURE "textures/exit/hole.xpm"
# define UNBLOCKED_EXIT_TEXTURE "textures/exit/hole_ladder.xpm"
# define FLOOR_TEXTURE "textures/floor/grass.xpm"
# define FLOOR_VARIATION_TEXTURE "textures/floor/flower.xpm"
# define ENEMY_LEFT_TEXTURE "textures/trainer/trainer_left.xpm"
# define ENEMY_RIGHT_TEXTURE "textures/trainer/trainer_right.xpm"
# define ENEMY_UP_TEXTURE "textures/trainer/trainer_up.xpm"
# define ENEMY_DOWN_TEXTURE "textures/trainer/trainer_down.xpm"
# define PATH_HORIZONTAL "textures/path/horizontal.xpm"
# define PATH_VERTICAL "textures/path/vertical.xpm"
# define PATH_CROSSING "textures/path/crossing.xpm"
# define SHRUB_TEXTURE "textures/path/crossing.xpm" // juiste texture

# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define UP_ARROW_KEY 126
# define DOWN_ARROW_KEY 125
# define LEFT_ARROW_KEY 123
# define RIGHT_ARROW_KEY 124
# define ESC_KEY 53

/*
** for every {DENSITIE_SHROB} floor there wil be 1 flower
** the bigger the number, the less flowers
*/
# define DENSITIE_FLOOR_VAR 25

/*
** for every {MOVEMENTSPEED} frame the entities will move
** the bigger the number, the slower the enemy
*/
# define MOVEMENT_SPEED 25


typedef enum	e_texture_dir
{
	text_up,
	text_down,
	text_right,
	text_left
}				t_texture_dir;

typedef enum	e_tile_sides
{
	front,
	back,
	right,
	left,
	current
}				t_tile_sides;

typedef	struct	s_2int
{
	int			x;
	int			y;
}				t_2int;

typedef struct	s_vla
{
	char		**array;
	int			size;
	int			capacity;
}				t_vla;

typedef struct		s_map_validation
{
	unsigned int	amount_players;
	unsigned int	amount_collectibles;
	unsigned int	amount_exit;
	unsigned int	amount_enemy;
	unsigned int	amount_floor;
	unsigned int	map_len;
	bool			equal_map_len;
}					t_map_validation;

typedef struct		s_move
{
	bool			up;
	bool			down;
	bool			right;
	bool			left;
}					t_move;
/*
** utils image elem
*/
typedef struct  	s_imginfo
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_width;
	int				img_height;
	bool			is_sprite;
}					t_imginfo;

typedef struct 	s_window
{
	void		*frame;
	int			frame_rate;
	int			max_texture_size;
	t_2int		viewable_mapsize;
	char		**map_to_show;
}				t_window;


typedef struct	s_textures
{
	t_imginfo	wall;
	t_imginfo	player;
	t_imginfo	collectible;
	t_imginfo	unblocked_exit;
	t_imginfo	blocked_exit;
	t_imginfo	enemy[4];
	t_imginfo	enemy_left;
	t_imginfo	enemy_right;
	t_imginfo	enemy_up;
	t_imginfo	enemy_down;
	t_imginfo	floor;
	t_imginfo	floor_variation;
	t_imginfo	path_vertical;
	t_imginfo	path_horizontal;
	t_imginfo	path_crossing;
}				t_textures;

typedef struct	s_mapinfo
{
	char		**map;
	t_2int		size;
	int			tokens;
}				t_mapinfo;

typedef struct	s_entity
{
	t_2int		pos;
	t_2int		delta;
}				t_entity;

typedef struct	s_bot
{
	int			amount;
	t_entity	*array;
}				t_bot;

typedef struct	s_gamedata
{
	void		*mlx;
	t_window	window;
	t_move		move;
	t_mapinfo	mapinfo;
	t_textures	textures;
	t_imginfo	img;
	t_entity	player;
	t_bot		enemy;
}				t_gamedata;

void	exit_with_message(char *message, int exitcode);

int		str_is_only_char(char *str, char c);
int		ft_arraylen(char **array);
int		get_exponent(int base, int power);
void	print_map(char **array);
void	my_mlx_pixel_put(t_imginfo *img, int x, int y, int color);

void	vla_shrink(t_vla *vla);
void	vla_add_line_to_array(t_vla* vla, char *line);
void	vla_init(t_vla* vla);

void	move_player(t_entity *player, t_bot *enemies, t_mapinfo* mapinfo);
void	move_enemies(char **map, t_bot *enemies, t_entity *player);

int		key_press(int keycode, t_move *move);

void	make_frame(t_gamedata* gamedata);

void	map_validation(char **map, int* amount_collectibles, int *amount_enemy);

void	parse_map(char *filename, t_gamedata *gamedata);
void	get_window(t_window* window, void* mlx, t_2int mapsize);
void	get_textures(t_textures* textures, void *mlx);
void	get_image(t_imginfo* img, void* mlx, t_2int gridsize, int texturesize);

#endif
