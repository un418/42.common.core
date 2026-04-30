SHELL		= /bin/sh

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
HEADER		= ft_printf.h

SRCS		= 

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
