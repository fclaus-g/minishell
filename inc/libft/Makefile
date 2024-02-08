# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 09:29:12 by pgomez-r          #+#    #+#              #
#    Updated: 2024/02/08 10:08:29 by fclaus-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = $(wildcard *.c)

OBJS	=	$(SRCS:.c=.o)
			
CC		= gcc

RM		= rm -f

CFLAGS	= -g -Wall -Wextra -Werror

NAME = libft.a

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "\033[0;32m\n	 #####Libft42 compilada! #####\n\033[0m"

all: $(NAME)

%.o: %.c
	@$(CC) -c $(CFLAGS) $?

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY:	all clean fclean re bonus