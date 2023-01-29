# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 09:30:00 by lrosa-do          #+#    #+#              #
#    Updated: 2023/01/13 18:30:11 by lrosa-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
INCLUDES = ../includes/minishell.h libraries/libft/include/libft.h
LIBFT = libraries/libft
SRC_PATH = ./source/
CC		= cc
libft = ./libraries/libft/libft.a

SRC = $(SRC_PATH)main.c\
			$(SRC_PATH)table/arraytable.c\
			$(SRC_PATH)table/array_by_key.c\
			$(SRC_PATH)table/array_to_str_arr.c\
			$(SRC_PATH)table/variable.c\
			$(SRC_PATH)table/free_table.c\
			$(SRC_PATH)table/table_utils.c\
			$(SRC_PATH)builtins/changedir.c\
			$(SRC_PATH)builtins/changedir_control.c\
			$(SRC_PATH)builtins/built_echo.c\
			$(SRC_PATH)builtins/built_env.c\
			$(SRC_PATH)builtins/built_pwd.c\
			$(SRC_PATH)builtins/built_exit.c\
			$(SRC_PATH)builtins/built_unset.c\
			$(SRC_PATH)builtins/built_export.c\
			$(SRC_PATH)builtins/export_utils_a.c\
			$(SRC_PATH)builtins/export_utils_b.c\
			$(SRC_PATH)parser/split_args_a.c\
			$(SRC_PATH)parser/split_args_b.c\
			$(SRC_PATH)parser/split_args_c.c\
			$(SRC_PATH)parser/split_control_0.c\
			$(SRC_PATH)parser/split_control_1.c\
			$(SRC_PATH)parser/split_control_2.c\
			$(SRC_PATH)parser/set_space_for_redir.c\
			$(SRC_PATH)pipe_redirect/cmd_for_redirect.c\
			$(SRC_PATH)pipe_redirect/logic_fd.c\
			$(SRC_PATH)pipe_redirect/cmd_pipe.c\
			$(SRC_PATH)pipe_redirect/redirect.c\
			$(SRC_PATH)pipe_redirect/here_doc.c\
			$(SRC_PATH)execute/execute.c\
			$(SRC_PATH)execute/execve.c\
			$(SRC_PATH)execute/exec_utils.c\
			$(SRC_PATH)signal.c\
			$(SRC_PATH)eval_change.c\
			$(SRC_PATH)termios_shell.c\
			$(SRC_PATH)paths_n_prompt.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		@make -C $(LIBFT)
		@$(CC) $(CFLAGS)  -o $@ $^ $(libft) -lreadline -I includes 
		@echo "\e[91m" " Create "  "\e[0m($@)"  "\e[0m"

%.o: %.c
		@$(CC) $(CFLAGS) -c -o $@ $< -I includes
		@echo "\e[91m" " Compile " "\e[0m ($<)" "\e[91m" "  object" "\e[0m ($@)"


clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)
	@echo "\e[91m" " Clean  obs" "\e[0m"

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME) $(OBJS)
	@echo "\e[91m" " Delete   bin" "\e[0m"

re: fclean all

