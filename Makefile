# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 19:00:12 by hzimmerm          #+#    #+#              #
#    Updated: 2024/05/11 19:01:35 by hzimmerm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = checker
CFLAGS = -g -Wall -Wextra -Werror -Ihome/hzimmerm/projects/libft_bonus_tobecopied \
	-Ihome/hzimmerm/projects/ft_printf
SRCS = srcs/main.c
LDFLAGS = -fsanitize=address
LIBFT = /home/hzimmerm/projects/libft_bonus_tobecopied/libft.a
LIB = /home/hzimmerm/projects/libft_bonus_tobecopied
PRINTFLIBFT = /home/hzimmerm/projects/ft_printf/libftprintf.a
PRINTF = /home/hzimmerm/projects/ft_printf
OBJS = $(SRCS:.c=.o)
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	@if [ ! -f "$(LIBFT)" ]; then \
		make -C $(LIB); \
	fi
	@if [ ! -f "$(PRINTLIBFT)" ]; then \
		make -C $(PRINTF); \
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
