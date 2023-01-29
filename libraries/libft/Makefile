# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/19 09:30:00 by lrosa-do          #+#    #+#              #
#    Updated: 2023/01/07 19:12:16 by lrosa-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

DIR_SRCS	= src
DIR_OBJS	= objs
SUBDIRS		= char fd mem string list ntl printf

SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_SRCS)/, $(dir)))
OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_OBJS)/, $(dir)))
SRCS		= $(foreach dir, $(SRCS_DIRS), $(wildcard $(dir)/*.c))
OBJS		= $(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.c=.o))

INCLUDES	= -I include

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= /bin/rm -f

$(DIR_OBJS)/%.o :	$(DIR_SRCS)/%.c
			@mkdir -p $(DIR_OBJS) $(OBJS_DIRS)
			@echo "\e[91m" " Compile " "\e[0m ($<)" "\e[91m" "  object" "\e[0m ($@)"
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar -rcs $(NAME) $(OBJS)
			@ranlib $(NAME)
			@echo "\e[91m" " Create "  "\e[0m($@)" "lib" "\e[0m"

clean:
			@$(RM) $(OBJS)
			@$(RM) -r $(DIR_OBJS)
			@echo "\e[91m" " Clean  obs" "\e[0m"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\e[91m" " Delete   all" "\e[0m"

re:			fclean all

.PHONY:		all clean fclean re
