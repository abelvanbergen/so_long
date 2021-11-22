# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abelfranciscusvanbergen <abelfranciscus      +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/18 19:37:36 by abelfrancis   #+#    #+#                  #
<<<<<<< HEAD
#    Updated: 2021/11/19 08:57:47 by avan-ber      ########   odam.nl          #
=======
#    Updated: 2021/11/21 15:18:32 by abelfrancis   ########   odam.nl          #
>>>>>>> e8d93ff62348f1517c4f76bd74618cbb51450f1b
#                                                                              #
# **************************************************************************** #

NAME = so_long

CFLAGS = -Wall -Werror -Wextra

OBJ_DIR = objs
SRC_DIR = srcs

_OBJ_FILES =	main \
				error \
				get_textures \
				map_validation \
				parse \
				utils \
				vla \
				windowsetup
				


OBJ_FILES = $(addsuffix .o, $(addprefix $(OBJ_DIR)/,$(_OBJ_FILES)))

# locations librarys
MLX_LOC		= lib/mlx
LIBFT_LOC	= lib/libft
GNL_LOC		= lib/get_next_line
SO_LONG_LOC = includes
# librarys
<<<<<<< HEAD
LIBS		=	-L $(MLX_LOC) -lmlx \
				-L $(LIBFT_LOC) -lft\
=======
LIBS		=	-L $(LIBFT_LOC) -lft\
				-L $(MLX_LOC) -lmlx\
>>>>>>> e8d93ff62348f1517c4f76bd74618cbb51450f1b
				-L $(GNL_LOC) -lgnl

FRAMEWORK =	-framework OpenGl\
			-framework AppKit

#includes
INCLUDES	=	-I $(SO_LONG_LOC) \
				-I $(LIBFT_LOC) \
				-I $(MLX_LOC) \
				-I $(GNL_LOC)

#colors
RESET =		\x1b[0m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	cp lib/mlx/libmlx.dylib .
	make bonus -C $(LIBFT_LOC)
	make bonus -C $(GNL_LOC)
	$(CC) $(FLAGS) $(LIBS) $(FRAMEWORK) -o $(NAME) $(OBJ_FILES) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/$(dir $*)
	gcc -c $(CFLAGS) $(INCLUDES) -I . $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_LOC) clean
	$(MAKE) -C $(GNL_LOC) clean

fclean: clean
<<<<<<< HEAD
	make clean -C $(MLX_LOC)
	rm -rf libmlx.dylib lib/mlx/libmlx.dylib
	make fclean -C $(LIBFT_LOC)
	rm -f $(LIBFT_LOC)/libft.a
	make fclean -C $(GNL_LOC)
=======
	# make clean -C $(MLX_LOC)
	# rm -rf libmlx.dylib lib/mlx/libmlx.dylib
	rm -rf libmlx.dylib
	$(MAKE) -C $(LIBFT_LOC) fclean
	$(MAKE) -C $(GNL_LOC) fclean
>>>>>>> e8d93ff62348f1517c4f76bd74618cbb51450f1b
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
