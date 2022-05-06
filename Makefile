# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 19:15:54 by qduong            #+#    #+#              #
#    Updated: 2022/05/06 16:56:23 by qduong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Werror -Wextra
SRCS = philo.c utils.c checks.c main.c threads.c eat.c
OBJS = ${SRCS:.c=.o}
RM = rm -f
CC = gcc

all: $(NAME)

$(NAME) : ${OBJS}
	$(CC) -g $(CFLAGS) -o $(NAME) ${OBJS}

clean:
	${RM} ${OBJS} $(BONUS_OBJS)

fclean: clean
	${RM} $(NAME) 

re: fclean all

.PHONY:	all clean fclean re 

no:
	norminette $(SRCS)
