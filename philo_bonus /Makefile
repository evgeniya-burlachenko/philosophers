# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 12:15:49 by skelly            #+#    #+#              #
#    Updated: 2021/11/12 17:59:42 by skelly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo_bonus

HEADER			=	philo.h

SRCS			=	init.c \
					main.c \
					utils.c 
				
OBJS			=	$(patsubst %.c, %.o, $(SRCS))


CFLAGS			=	-Wall -Wextra -Werror -pthread -fsanitize=address -g
CC 				=	gcc

RM				=	rm -f

all: $(NAME) 

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "philosophers are ready"
	
%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c  $< -o $@
		
norm:
	@norminette . | grep Error

clean:
	@$(RM) $(OBJS) 

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean bonus