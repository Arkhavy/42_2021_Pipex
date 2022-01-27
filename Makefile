# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljohnson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/12 07:59:29 by ljohnson          #+#    #+#              #
#    Updated: 2022/01/23 09:42:55 by ljohnson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = pipex
NAME_BONUS = pipex_bonus
LIBFT = libft/libft.a

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

SRCS =	px_src/pipex.c		\
		px_src/px_parsing.c	\
		px_src/px_program.c
SRCS_BONUS =	px_src_bonus/pipex_bonus.c		\
				px_src_bonus/px_parsing_bonus.c	\
				px_src_bonus/px_program_bonus.c

HEAD = px_inc/pipex.h
HEAD_BONUS = px_inc_bonus/pipex_bonus.h

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

#//////////////////////////////////////////////////////////////////////////////
#		COMMAND SHORTCUTS
#//////////////////////////////////////////////////////////////////////////////

CC = gcc
CF = -Wall -Wextra -Werror
CI = -I
CS = -g -fsanitize=address
CG = -g3

RM = rm -rf

#//////////////////////////////////////////////////////////////////////////////
#		RULES
#//////////////////////////////////////////////////////////////////////////////

all: ${NAME} ${LIBFT}

# Binary creation

${NAME}: ${OBJS} ${HEAD} ${LIBFT} Makefile
	${CC} ${CF} ${OBJS} ${LIBFT} -o ${NAME}
	
${NAME_BONUS}: ${OBJS_BONUS} ${HEAD_BONUS} ${LIBFT} Makefile
	${CC} ${CF} ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}

bonus: ${NAME_BONUS}

%.o : %.c ${HEAD} ${LIBFT}
	${CC} -c ${CF} $< -o ${<:.c=.o}

${LIBFT}: libft/Makefile
	make -j 3 -C libft/

# Mandatory rules

clean:
	@${RM} ${OBJS} ${OBJS_BONUS}
	@echo removed obj files

fclean: clean
	${RM} ${NAME}
	${RM} ${NAME_BONUS}
	make fclean -C libft/

re: fclean all

reb: fclean bonus