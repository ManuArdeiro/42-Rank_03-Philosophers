# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ardeiro <Ardeiro@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:46:18 by jolopez-          #+#    #+#              #
#    Updated: 2023/12/26 23:51:55 by Ardeiro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= philosophers

vpath 		%.h	include
vpath 		%.o	obj
vpath 		%.c	src 

INCLUDE		= -Iinclude/

CC			= gcc -Wall -Wextra -Werror

RM			= rm -rf

SRC			= atoi.c routine.c structs.c philosophers.c utils.c threads.c mem.c 

OBJ_DIR		= obj

OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	$(COMPILE.c) $< -o $@

$(NAME):	$(OBJ)
			@echo "$(YELLOW)	Creating philosophers...	$(WHITE)"
			$(CC) $(OBJ) -o $(NAME)
			@echo "\n$(LIGHT_GRAY)	--- Philisophers Ready ---	\n"

all:		$(NAME)

clean:
			@echo "\n"
			@echo "$(LIGHT_RED) Cleaning object files... $(WHITE)\n"
			/bin/rm -rf $(OBJ_DIR)
			@echo "$(GREEN) *** **** DONE **** *** $(WHITE)\n"

fclean:		clean
			@echo "\n"
			@echo "$(LIGHT_RED) Cleaning philosophers executable file... $(WHITE)\n"
			$(RM) $(NAME)
			@echo "$(GREEN) *** **** DONE **** *** $(WHITE)\n"

re:			clean all

.PHONY:		all fclean clean re

# COLORS
RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
CYAN			= \033[0;36m
LIGHT_GRAY		= \033[0;37m
DARK_GRAY		= \033[0;90m
LIGHT_RED		= \033[0;91m
WHITE			= \033[0;97m

#SETS
BOLD			= \e[0;1m
UNDERLINED		= \e[0;4m
BLINK			= \e[0;5m