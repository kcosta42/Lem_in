# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 10:00:00 by kcosta            #+#    #+#              #
#    Updated: 2019/03/08 18:22:30 by kcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = $(shell echo "\033[1m")
BOLD_END = $(shell echo "\033[21m")
RED = $(shell echo "\033[31m")
GREEN = $(shell echo "\033[32m")
YELLOW = $(shell echo "\033[33m")
BLUE = $(shell echo "\033[34m")
MAGENTA = $(shell echo "\033[35m")
EOC = $(shell echo "\033[0m")

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/
LIB = -L $(LIBFT) -lft
NAME = lem-in
SRCS_PATH = srcs/
INCLUDES_PATH = includes/
INCLUDES = -I includes/ -I libft/includes/
FILES = lem_in.c \
		singletons.c \
		parser.c \
		utils.c \
		solver.c \
		ft_strisdigit.c
SRCS = $(addprefix $(SRCS_PATH), $(FILES))
OBJS = $(SRCS:.c=.o)

all: lib $(NAME)

lib :
	git submodule init
	git submodule update --remote
	@make -C $(LIBFT)

%.o: %.c
	@/bin/echo -n $(YELLOW)[$(GREEN)$(BOLD)Compiling $(BLUE)$(notdir $@) $(EOC)$(YELLOW)...]- -$(EOC)
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<
	@echo "$(YELLOW)[$(BOLD)$(GREEN)Done!$(EOC)$(YELLOW)]$(EOC)"

$(NAME): $(OBJS)
	@/bin/echo $(YELLOW)[$(MAGENTA)$(BOLD)Creating $(BLUE)$(NAME) $(EOC)$(YELLOW)...]$(EOC)
	@$(CC) $(FLAGS) -o $(NAME) $(INCLUDES) $(OBJS) $(LIB)
	@/bin/echo "$(YELLOW)[$(BOLD)$(BLUE)$(NAME) $(MAGENTA)Created!$(EOC)$(YELLOW)]$(EOC)"

clean:
	@/bin/echo "$(YELLOW)[$(RED)$(BOLD)Cleaning $(EOC)$(YELLOW)...]$(EOC)"
	@/bin/rm -f $(OBJS)
	@make -C $(LIBFT) clean &> /dev/null
	@/bin/echo "$(YELLOW)[$(RED)$(BOLD)All .o Removed!$(EOC)$(YELLOW)]$(EOC)"

fclean: clean
	@make -C $(LIBFT) fclean &> /dev/null
	@/bin/rm -f $(NAME)
	@/bin/echo "$(YELLOW)[$(BOLD)$(BLUE)$(NAME) $(RED)Removed!$(EOC)$(YELLOW)]$(EOC)"

re: fclean all
