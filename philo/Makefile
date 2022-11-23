# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 10:52:12 by sdos-san          #+#    #+#              #
#    Updated: 2022/11/23 16:31:41 by sdos-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#      NAME       #
NAME		=	philo

#      FLAGS      #

CC			=	cc
FLAGS		=	-g -Wall -Wextra -Werror -pthread
RM			=	rm -rf


#       MANDATORY    #

FILES	=	main \
			utils \
			errors \
			threads \
			utils \
			create_threads \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

.c.o: $(SRCS)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
		@$(CC) -o $@  $^
		@printf "$(GREEN)Philophers Compiled 😎\n"

all: $(NAME)

clean:
		@printf "$(YELLOW)Deleting the Philophers Objects...\n"
		@$(RM) $(OBJS)
		@printf "$(GREEN)Philophers Objects Deleted 😎 🗑\n"

fclean:	clean
		@printf "$(YELLOW)Deleting Philophers 🔪...\n"
		@$(RM) $(NAME)
		@printf "$(GREEN)Philophers Deleted 😎 🗑 💀\n"

re:				fclean all

.PHONY:		all clean fclean re

GREEN=\033[0;32m
YELLOW=\033[0;33m
