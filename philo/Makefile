# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 12:15:49 by skelly            #+#    #+#              #
#    Updated: 2021/11/12 23:39:59 by skelly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
HEADER			=	philo.h
SRCS			=	main.c init.c utils.c simulate.c
OBJS			=	$(patsubst %.c, %.o, $(SRCS))
CFLAGS			=	-Wall -Wextra -Werror -pthread 
CC 				=	gcc
RM				=	rm -f

all:  $(NAME) 

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "\033[0;35mphilosophers are ready"
	
%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c  $< -o $@
		
norm:
	norminette . | grep Error

clean:
	@$(RM) $(OBJS) 

fclean: clean
	@echo "\033[0;34mphilosophers clean"
	@ $(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean bonus