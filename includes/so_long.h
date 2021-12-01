/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 19:26:10 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/12/01 17:42:32 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stddef.h>
# include "mlx.h"
# include "libft.h"

/*
** So long config --------------------------------------------------------------
**
** max size of window
*/
# define WINDOW_WITDH 1920
# define WINDOW_HEIGHT 1080
/*
** size of window in textures
*/
# define VIEWABLE_WITDH 25
# define VIEWABLE_HEIGHT 15
/*
** Must be a power of 2
*/
# define VIEWABLE_TEXTURE_SIZE 256
/*
** for every {DENSITIE_SHROB} floor there wil be 1 flower
** the bigger the number, the less flowers
*/
# define DENSITIE_FLOOR_VAR 25
/*
** for every {MOVEMENTSPEED} frame the entities will move
** the bigger the number, the slower the enemy
*/
# define MOVEMENT_SPEED_ENEMY 35
# define MOVEMENT_SPEED_POKEMON 64
/*
** the size with what read will read
** the bigger the number, the less read calls are done
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
/*
**==============================================================================
*/



/*
** textures --------------------------------------------------------------------
**
** map
*/
# define WALL_TEXTURE "textures/wall/rock_2.xpm"
# define FLOOR_TEXTURE "textures/floor/grass.xpm"
# define FLOOR_VARIATION_TEXTURE "textures/floor/flower.xpm"

# define BLOCKED_EXIT_TEXTURE "textures/exit/boss.xpm"

# define COLLECTIBLE_TEXTURE "textures/pokebal/ball.xpm"

# define PATH_HORIZONTAL "textures/path/horizontal.xpm"
# define PATH_VERTICAL "textures/path/vertical.xpm"
# define PATH_CROSSING "textures/path/crossing.xpm"

# define SHRUB_TEXTURE "textures/floor/shrub.xpm"
/*
** player/trainer
*/
# define PLAYER_TEXTURE_LOC "textures/trainer/"
/*
** pikachu
*/
# define PIKACHU_TEXTURE_LOC "textures/pikachu/"
# define PIKACHU_NAMING_CONV "00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 \
16 17 18 19 20 21 22 23 24"
# define DIFFERENT_PIKACHU 25
/*
** enemy
*/
# define ENEMIES_TEXTURE_LOC "textures/enemy/"
# define DIFFERENT_ENEMIES 2
# define ENEMIES "woman/ man/"
/*
** Pokemon
*/
# define POKEMANY_TEXTURES_LOC "textures/pokemany/"
# define DIFFERENT_POKEMON 16
# define POKEMANY "aerodactyl/ arboc/ blastoise/ cadabra/ charmander/ diglett/ \
eevee/ gengar/ growlithe/ machamp/ magnetron/ meowth/ mewtwo/ muk/ peugeot/ \
ponyta/"
/*
** Utils
*/
# define TEXTURE_DIRECTIONS "up right down left current"
/*
**==============================================================================
*/



/*
** textures --------------------------------------------------------------------
** map
*/
# define VALID_MAP_CHAR "10CEP<>^v-|+.#"

# define WALL_CHAR '1'
# define FLOOR_CHAR '0'
# define PLAYER_CHAR 'P'
# define COLLECTIBLE_CHAR 'C'
# define EXIT_CHAR 'E'
# define FLOOR_VARIATION_CHAR '2'
/*
** enemy
*/
# define ENEMY_CHARS "<>^v"
# define ENEMY_CHAR_UP '^'
# define ENEMY_CHAR_DOWN 'v'
# define ENEMY_CHAR_LEFT '<'
# define ENEMY_CHAR_RIGHT '>'
/*
** path
*/
# define ENEMY_PATH_VERTICAL '|'
# define ENEMY_PATH_HORIZONTAL '-'
# define ENEMY_PATH_CROSSING '+'
/*
** pokemon
*/
# define POKEMON_WALK_CHARS ".#"
# define POKEMON_WALK_SHRUB_CHAR '#'
# define POKEMON_WALK_PLAIN_CHAR '.'
/*
**==============================================================================
*/



/*
** Keycodes --------------------------------------------------------------------
*/
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
**==============================================================================
*/



/*
** enums -----------------------------------------------------------------------
*/
/*
** used to get the right texture by the direction
*/
typedef enum	e_texture_dir
{
	text_up,
	text_right,
	text_down,
	text_left,
	text_current
}				t_texture_dir;
/*
** used by the movement of the bots
*/
typedef enum	e_tile_sides
{
	front,
	back,
	right,
	left,
	current
}				t_tile_sides;
/*
**==============================================================================
*/

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
	unsigned int	amount_pokemon_spawn;
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
	t_imginfo	*player;
	t_imginfo	collectible;
	t_imginfo	blocked_exit;
	t_imginfo	**enemy;
	t_imginfo	**pokemany;
	t_imginfo	*pikachu;
	t_imginfo	floor;
	t_imginfo	floor_variation;
	t_imginfo	path_vertical;
	t_imginfo	path_horizontal;
	t_imginfo	path_crossing;
	t_imginfo	shrub;
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
	int			texture_id;
	int			pokeballs;
	int			pokemon;
	int			enemies_defeated;
	bool		moved;
	bool		shown;
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
	int			move_counter;
	t_bot		enemy;
	t_bot		pokemany;
}				t_gamedata;

/*
** utils
*/
void	exit_with_message(char *message, int exitcode);
void	exit_with_2_messages(char *message1, char *message2, int exitcode);

int		key_press(int keycode, t_move *move);

void	vla_shrink(t_vla *vla);
void	vla_add_line_to_array(t_vla *vla, char *line);
void	vla_init(t_vla *vla);

void	print_map(char **map);
void	free_double_array(char **array);
int		ft_arraylen(char **array);

int		str_is_only_char(char *str, char c);
char	*ft_strjoin_and_free(char *str1, char *str2);
char	*ft_strjoin3(char *str1, char *str2, char *str3);

int		get_exponent(int base, int power);
void	my_mlx_pixel_put(t_imginfo *img, int x, int y, int color);
void	*malloc_check(void *content);
/*
** parse
*/
void	set_entity(t_entity *dest, t_2int pos, int texture_id);
void	set_pokemany(t_bot *pokemany, int pokemon_spawn, char **map);
void	set_player_and_enemies(t_entity *player, t_bot *enemy, char **map);
void	set_entities(t_gamedata *gamedata, int amount_pokemon_spawn);

bool	is_map_seperated(char *map);

void	map_validation(char **map, t_map_validation *validation);

void	parse_map(char *filename, t_gamedata *gamedata);
/*
** setup
*/
void	get_textures(t_textures *textures, void *mlx);

void	get_window(t_window *window, void *mlx, t_2int mapsize);

void	get_image(t_imginfo *img, void *mlx, t_2int gridsize, int texturesize);
/*
** make frame
*/
void	write_texture_img(t_imginfo *img, t_imginfo *texture,
			t_2int start, int max_texture_size);

void	write_map(t_gamedata *gamedata, t_2int *start_map_to_show);
void	write_shrub(char **map, t_imginfo *img,
			t_imginfo *shrub_text, int max_text_size);

void	write_entities(t_gamedata *gamedata, t_2int *start);
void	write_pikachu(t_gamedata *gamedata, t_2int loc, int max_texture_size);

void	set_map_to_show(t_gamedata *gamedata, t_2int *start);

void	make_frame(t_gamedata *gamedata);
/*
** hook
*/
void	pokemon_moved_on_pokemon(t_entity *moved, t_entity *collided);
void	turn_enemies_backwards(t_entity *moved, t_entity *collided);
void	player_try_catch_pokemon(t_entity *player, t_entity *pokemon);
void	player_moved_on_enemy(t_entity *player, t_entity *enemy);
bool	is_next_pos_entity(t_bot *entities,
			t_entity *entity, void (*f)(t_entity *, t_entity *));
/*
** move
*/
bool	is_face_to_face(t_entity *a, t_entity *b);
void	turn(t_2int *delta, t_tile_sides direction);
char	get_tile(int x, int y, char **map);
char	*set_sides(char *tiles, t_entity *entity, char **map);
void	move_entity_pos(t_entity *entity);

void	move_player(t_entity *player, t_bot *enemies,
			t_bot *pokemany, t_mapinfo *mapinfo);

void	move_enemies(char **map, t_bot *enemies, t_entity *player);

void	move_pokemany(t_gamedata *gamedata, t_bot *pokemany);

#endif
