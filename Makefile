# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 14:16:49 by ayusa             #+#    #+#              #
#    Updated: 2025/05/14 17:51:27 by ayusa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar rcs
RM      = rm -f

MANDAT_SRCS = get_next_line.c get_next_line_utils.c
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

MANDAT_OBJS = $(MANDAT_SRCS:.c=.o)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

OBJS = $(MANDAT_OBJS)

ifdef WITH_BONUS
OBJS += $(BONUS_OBJS)
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus:
	@make WITH_BONUS=1

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
