# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-ber <avan-ber@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/30 16:03:32 by avan-ber       #+#    #+#                 #
#    Updated: 2019/11/12 14:38:37 by avan-ber      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft
FLAGS = -Wall -Wextra -Werror
OBJECTS = 	ft_atoi.o \
		ft_bzero.o \
		ft_calloc.o \
		ft_isalnum.o \
		ft_isalpha.o \
		ft_isascii.o \
		ft_isdigit.o \
		ft_isprint.o \
		ft_itoa.o \
		ft_memccpy.o \
		ft_memchr.o \
		ft_memcmp.o \
		ft_memcpy.o \
		ft_memmove.o \
		ft_memset.o \
		ft_putchar_fd.o \
		ft_putendl_fd.o \
		ft_putnbr_fd.o \
		ft_putstr_fd.o \
		ft_split.o \
		ft_strchr.o \
		ft_strdup.o \
		ft_strjoin.o \
		ft_strlcat.o \
		ft_strlcpy.o \
		ft_strlen.o \
		ft_strmapi.o \
		ft_strncmp.o \
		ft_strnstr.o \
		ft_strrchr.o \
		ft_strtrim.o \
		ft_substr.o \
		ft_tolower.o \
		ft_toupper.o
BONUS = ft_lstadd_back_bonus.o \
		ft_lstadd_front_bonus.o \
		ft_lstclear_bonus.o \
		ft_lstdelone_bonus.o \
		ft_lstiter_bonus.o \
		ft_lstlast_bonus.o \
		ft_lstmap_bonus.o \
		ft_lstnew_bonus.o \
		ft_lstsize_bonus.o
LBLUE =  \033[38;5;14m
BLUE =  \033[38;5;12m
RED =  \033[38;5;9m
YELLOW =  \033[38;5;11m
WHITE =  \033[38;5;7m


all: $(NAME)

%.o: %.c
	@echo "$(LBLUE)Compiling...		$(BLUE)$<"
	@gcc -c -o $@ $< $(FLAGS)

$(NAME): $(OBJECTS)
	@ echo "\n$(LBLUE)making			$(BLUE)$(NAME).a"
	@ ar rcs $(NAME).a $(OBJECTS)
	@ echo "$(RED)========================================"
	@ echo "$(RED)||                DONE                ||"
	@ echo "$(RED)========================================"



bonus: $(OBJECTS) $(BONUS)
	@echo "$(LBLUE)\nAdding bonus to		$(BLUE)$(NAME)"
	@ar rcs $(NAME).a $(OBJECTS) $(BONUS)
	@ echo "$(RED)========================================"
	@ echo "$(RED)||                DONE                ||"
	@ echo "$(RED)========================================"

clean:
	@ echo "\n$(LBLUE)removing 		$(BLUE)objects"
	@ /bin/rm -f $(OBJECTS)
	@ /bin/rm -f $(BONUS)
	@ echo "$(RED)========================================"
	@ echo "$(RED)||                DONE                ||"
	@ echo "$(RED)========================================"

fclean: clean
	@ echo "\n$(LBLUE)removing 		$(BLUE)$(NAME).a"
	@ /bin/rm -f 	$(NAME).a
	@ echo "$(RED)========================================"
	@ echo "$(RED)||                DONE                ||"
	@ echo "$(RED)========================================\n"

re: fclean all

.PHONY: all clean fclean re
