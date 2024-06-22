# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/08 13:48:45 by ksellami          #+#    #+#              #
#    Updated: 2024/06/22 14:29:16 by ksellami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
HEADER = minishell.h
FILES =   main.c libft_utils.c ft_split.c nodes_utils.c  parsing.c fixdelimiters.c tokenize.c  expand.c ft_splite2.c execute.c
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