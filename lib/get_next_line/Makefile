# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abelfranciscusvanbergen <abelfranciscus      +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/18 19:28:19 by abelfrancis   #+#    #+#                  #
#    Updated: 2021/11/18 19:28:37 by abelfrancis   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libgnl
FLAGS = -Wall -Wextra -Werror
OBJECTS =	get_next_line.o \
			get_next_line_utils.o
BONUS = 	get_next_line_bonus.o \
			get_next_line_utils_bonus.o

LBLUE =		\033[38;5;14m
BLUE =		\033[38;5;12m
RED =		\033[38;5;9m
YELLOW =	\033[38;5;11m
WHITE =		\033[38;5;7m
NORMAL =	\033[0;0m


all: $(NAME)

%.o: %.c
	@echo "$(LBLUE)Compiling...		$(BLUE)$<"
	@gcc -c -o $@ $< $(FLAGS)

$(NAME): $(OBJECTS)
	@ echo "\n$(LBLUE)making		        $(BLUE)$(NAME).a"
	@ ar rcs $(NAME).a $(OBJECTS)
	@ echo "$(RED)========================================"
	@ echo "$(RED)||                DONE                ||"
	@ echo "$(RED)========================================$(NORMAL)"

bonus: $(BONUS)
	@echo "\n$(LBLUE)making 		   $(BLUE)$(NAME).a"
	@ar rcs $(NAME).a $(BONUS)
	@ echo "$(RED)========================================"
	@ echo "$(RED)||                DONE                ||"
	@ echo "$(RED)========================================$(NORMAL)"

clean:
	@ echo "\n$(LBLUE)removing 		$(BLUE)objects"
	@ /bin/rm -f $(OBJECTS)
	@ /bin/rm -f $(BONUS)
	@ echo "$(RED)========================================"
	@ echo "$(RED)||                DONE                ||"
	@ echo "$(RED)========================================$(NORMAL)"

fclean: clean
	@ echo "\n$(LBLUE)removing 		$(BLUE)$(NAME).a"
	@ /bin/rm -f 	$(NAME).a
	@ echo "\n$(LBLUE)removing          $(BLUE)$(NAME)_bonus.a"
	@ /bin/rm -f 	$(NAME)_bonus.a
	@ echo "$(RED)========================================"
	@ echo "$(RED)||                DONE                ||"
	@ echo "$(RED)========================================\n$(NORMAL)"

re: fclean all

.PHONY: all clean fclean re
