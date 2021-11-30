# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abelfranciscusvanbergen <abelfranciscus      +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/18 19:37:36 by abelfrancis   #+#    #+#                  #
#    Updated: 2021/11/30 17:44:05 by avan-ber      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CFLAGS = -Wall -Werror -Wextra -g

OBJ_DIR = objs
SRC_DIR = srcs

_OBJ_FILES =	main \
				game/frame/make_frame \
				game/frame/map_to_show \
				game/frame/write_entities \
				game/frame/write_map \
				game/frame/write_texture \
				game/move/collision \
				game/move/move_enemy \
				game/move/move_player \
				game/move/move_pokemon \
				game/move/utils \
				parse/entities/set_entities \
				parse/entities/set_player_and_enemy \
				parse/entities/set_pokemon \
				parse/map_seperation_check \
				parse/map_validation \
				parse/parse \
				setup/imagesetup \
				setup/texturesetup \
				setup/windowsetup \
				utils/array_utils \
				utils/error \
				utils/hooks \
				utils/str_utils \
				utils/utils \
				utils/vla


OBJ_FILES = $(addsuffix .o, $(addprefix $(OBJ_DIR)/,$(_OBJ_FILES)))

# locations librarys
MLX_LOC		= lib/mlx
LIBFT_LOC	= lib/libft
SO_LONG_LOC = includes
# librarys
LIBS		=	-L $(MLX_LOC) -lmlx \
				-L $(LIBFT_LOC) -lft

FRAMEWORK =	-framework OpenGl\
			-framework AppKit

#includes
INCLUDES	=	-I $(SO_LONG_LOC) \
				-I $(LIBFT_LOC) \
				-I $(MLX_LOC)

#colors
RESET =		\x1b[0m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make -C $(MLX_LOC)
	cp lib/mlx/libmlx.a .
	make bonus -C $(LIBFT_LOC)
	$(CC) $(FLAGS) $(LIBS) $(FRAMEWORK) -o $(NAME) $(OBJ_FILES) $(INCLUDES) -fsanitize=address -g

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(OBJ_DIR)/$(dir $*)
	gcc -c $(CFLAGS) $(INCLUDES) -I . $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_LOC) clean

fclean: clean
	make clean -C $(MLX_LOC)
	rm -rf libmlx.a lib/mlx/libmlx.a
	$(MAKE) -C $(LIBFT_LOC) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
