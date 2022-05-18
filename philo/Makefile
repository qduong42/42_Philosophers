# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 19:15:54 by qduong            #+#    #+#              #
#    Updated: 2022/05/18 14:34:03 by qduong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Werror -Wextra -pthread -g
SRCS = philo.c utils.c checks.c main.c threads.c eat.c
OBJS = ${SRCS:.c=.o}
RM = rm -f
CC = gcc

all: $(NAME)

$(NAME) : ${OBJS}
	$(CC) $(CFLAGS) -o $(NAME) ${OBJS}

debug: ${OBJS}
	$(CC) $(CFLAGS) -fsanitize=thread -o $(NAME) ${OBJS}

clean:
	${RM} ${OBJS} $(BONUS_OBJS)

fclean: clean
	${RM} $(NAME) 

re: fclean all

.PHONY:	all clean fclean re 

no:
	norminette $(SRCS)
