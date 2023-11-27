# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 21:48:21 by pgomez-r          #+#    #+#              #
#    Updated: 2023/11/17 11:19:02 by fclaus-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
LDFLAGS  = -lreadline
NAME     = minishell

SRC_PATH = src/
OBJ_PATH = obj/

SRC      = main.c init_structs.c init.c checkin.c builtins1.c exit.c
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
	@${MAKE} -C ./inc/libft
	@${CC} $(CFLAGS) $(OBJS) $(LDFLAGS) ./inc/libft/libft.a  -o $(NAME)
	@echo "\033[0;32m\n	 ##### Minishell is ready! #####\n\033[0m"

norm:
		@echo "\033[0;32m\n	 ##### Cheking 42_School_NORMINETTE #####\n\033[0m";
		@norminette src/
		@norminette inc/libft
		@norminette inc/minishell.h

debug:
		@gcc -Wall -Wextra -Werror -lreadline ./src/*.c ./inc/libft/libft.a -o debug 
		@echo "\033[0;32m\n	##### Debug file successfully generated #####\n\033[0m"

clean:
		@${RM} ${OBJS} ${BOBJS}
		@${MAKE} -C ./inc/libft clean
		@echo "\033[0;32m\n	##### Object files have been removed #####\n\033[0m"

fclean:	clean
		@${RM} ${NAME}
		@${MAKE} -C ./inc/libft fclean
		@${RM} ${BNAME} debug
		@echo "\033[0;32m\n	##### FCLEAN done! #####\n\033[0m"

re:	fclean all

.PHONY: all clean fclean re debug
