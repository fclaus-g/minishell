# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgomez-r <pgomez-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 21:48:21 by pgomez-r          #+#    #+#              #
#    Updated: 2023/11/01 21:57:59 by pgomez-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
NAME     = minishell

SRC_PATH = src/
OBJ_PATH = obj/

SRC      = main.c
SRCS	 = $(addprefix $(SRC_PATH), $(SRC))
OBJ		 = $(SRC:.c=.o)
OBJS	 = $(addprefix $(OBJ_PATH), $(OBJ))

RM       = rm -f

all:	${NAME}

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
$(NAME):	$(OBJS)
	@echo "\033[0;33m\n	 ##### Checking/compiling Libft_42 library #####\n\033[0m"
	@${MAKE} -C ./incl/libft
	@${CC} $(CFLAGS) $(OBJS) ./incl/libft/libft.a -o $(NAME)
	@echo "\033[0;32m\n	 ##### Minishell is ready! #####\n\033[0m"

norm:
		@echo "\033[0;32m\n	 ##### Cheking 42_School_NORMINETTE #####\n\033[0m";
		@norminette src/
		@norminette incl/libft
		@norminette incl/minishell.h

debug:
		@gcc -Wall -Wextra -Werror ./src/*.c ./incl/MLX42/libmlx42.a -o debug 
		@echo "\033[0;32m\n	##### Debug file successfully generated #####\n\033[0m"

clean:
		@${RM} ${OBJS} ${BOBJS}
		@${MAKE} -C ./incl/libft clean
		@echo "\033[0;32m\n	##### Object files have been removed #####\n\033[0m"

fclean:	clean
		@${RM} ${NAME}
		@${MAKE} -C ./incl/libft fclean
		@${RM} ${BNAME} debug
		@echo "\033[0;32m\n	##### FCLEAN done! #####\n\033[0m"

re:	fclean all

.PHONY: all clean fclean re debug
