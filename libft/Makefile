# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 19:35:33 by ksellami          #+#    #+#              #
#    Updated: 2024/07/24 12:07:10 by ksellami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FILES = ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strlcpy.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strcpy.c \
		ft_strncpy.c

FILES_BONUS = ft_lstnew_bonus.c \
			   ft_lstadd_front_bonus.c \
			   ft_lstsize_bonus.c \
			   ft_lstlast_bonus.c \
			 ft_lstadd_back_bonus.c  

OBJS = ${FILES:%.c=%.o}
OBJS_BONUS = ${FILES_BONUS:%.c=%.o}
CC = cc 
CFLAGS=-Wall -Wextra -Werror

all : $(NAME)
$(NAME): ${OBJS}
	ar rc ${NAME} ${OBJS}

bonus: ${OBJS_BONUS}
	ar rc ${NAME} ${OBJS_BONUS}
%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	rm -f ${NAME}

re: fclean all




