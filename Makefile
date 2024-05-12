# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 19:00:12 by hzimmerm          #+#    #+#              #
#    Updated: 2024/05/12 19:33:30 by Henriette        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = checker
CFLAGS = -g -Wall -Wextra -Werror -I../libft_rep -I../42_rep/printf
SRCS = srcs/main.c srcs/utils.c
LDFLAGS = -fsanitize=address
LIBFT = ../libft_rep/libft.a
PRINTFLIBFT = ../42_rep/printf/libftprintf.a
OBJS = $(SRCS:.c=.o)
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	@if [ ! -f "$(LIBFT)" ]; then \
		make -C ../libft_rep; \
	fi
	@if [ ! -f "$(PRINTLIBFT)" ]; then \
		make -C ../42_rep/printf; \
	fi
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTFLIBFT) $(LDFLAGS) -o $(NAME)
	chmod +x $(NAME)

%.o : %.c
	cc $(CFLAGS) -c $< -o $@
	
clean:
	$(RM) srcs/*.o $(PRINTF)/*.o $(LIB)/*.o

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(PRINTFLIBFT)

re: fclean $(NAME)

.PHONY: all clean fclean re
