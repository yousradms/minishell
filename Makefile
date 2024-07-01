# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/08 13:48:45 by ksellami          #+#    #+#              #
#    Updated: 2024/06/29 17:09:57 by ksellami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
HEADER = minishell.h
FILES =   main.c parsing/libft_utils.c parsing/ft_split.c parsing/nodes_utils.c  parsing/parsing.c parsing/fixdelimiters.c parsing/tokenize.c  parsing/expand.c parsing/ft_splite2.c  parsing/herdoc.c parsing/ft_split3.c parsing/print_debug.c execution/execute.c execution/ft_cd.c execution/builtins.c execution/ft_echo.c execution/ft_env.c execution/ft_exit.c execution/ft_export.c execution/ft_pwd.c execution/ft_unset.c execution/ft_split4.c execution/redirections.c execution/handle_pipes.c
OBJS = ${FILES:%.c=%.o}
CC = cc 
CFLAGS = -Wall -Wextra -Werror
all : $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ${OBJS} 
fclean: clean
	rm -f ${NAME}

re: fclean all