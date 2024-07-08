# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/08 13:48:45 by ksellami          #+#    #+#              #
#    Updated: 2024/07/08 09:02:11 by ksellami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h
FILES =   main.c parsing_execute.c \
parsing/utilsp/nodes_utils.c parsing/utilsp/set_env.c  parsing/utilsp/handle_quotes.c  parsing/utilsp/free_utils.c parsing/utilsp/command_utils.c parsing/utilsp/utils.c \
parsing/tokenize/fixdelimiters.c  parsing/tokenize/quote_delimiters.c parsing/tokenize/tokens_delimiter.c parsing/tokenize/tokenize.c parsing/tokenize/ft_split.c \
parsing/parser/ft_splite2.c parsing/parser/ft_split3.c parsing/ft_strtrim.c \
parsing/expand/expand.c parsing/expand/check_expand.c parsing/expand/expand_home_dir.c  parsing/expand/expand_variable.c \
parsing/heredoc/herdoc.c \
parsing/error_syntax/error_syntax.c parsing/error_syntax/open_her.c \
parsing/libft_utils.c parsing/print_debug.c \
execution/builtins/ft_cd.c execution/builtins/builtins.c execution/builtins/ft_echo.c execution/builtins/ft_env.c execution/builtins/ft_exit.c execution/builtins/ft_export.c execution/builtins/ft_pwd.c execution/builtins/ft_unset.c \
execution/redirections/redirections.c \
execution/execute/handle_pipes.c execution/execute/ft_split4.c execution/execute/execute_one_cmd.c execution/execute/handle_quotes.c \

OBJS = ${FILES:%.c=%.o}
CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
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