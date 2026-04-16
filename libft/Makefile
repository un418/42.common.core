SHELL		= /bin/sh

NAME		= libft.a

#To remove before submitting
TEST_FOLDER	= test
TEST_SRC	= test.c
TEST_OBJ	= test.o
DBG_OBJ		= debug.o

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DBGFLAGS	= -g

HEADER		= libft.h

SRCS		=	ft_isalpha.c	\
				ft_isdigit.c	\
				ft_isalnum.c	\
				ft_isascii.c	\
				ft_isprint.c	\
				ft_strlen.c		\
				ft_memset.c		\
				ft_bzero.c		\
				ft_memcpy.c		\
				ft_memmove.c	\
				ft_strlcpy.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME) test

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(DBGFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
# To remove before delivering the project
	rm -f $(TEST_OBJ)
	rm -f $(DBG_OBJ)
	
re: fclean all

# To remove before delivering the project
test: $(NAME)
	$(CC) $(CFLAGS)  $(TEST_SRC) -I. -L. -l:libft.a -o $(TEST_OBJ)
#	$(CC) $(CFLAGS)  $(TEST_SRC) -I. -L. -lft -o $(TEST_OBJ)
	./test.o

debug: $(NAME)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(TEST_SRC) -I. -L. -l:libft.a -o $(DBG_OBJ)
	./debug.o



# Find out why it don't work in another folder #TODO
#$(CC) $(CFLAGS) -c $(TEST_FOLDER)/$(TEST_SRC) -L. -l:libft.a -o $(TEST_FOLDER)/$(TEST_OBJ)
#./$(TEST_FOLDER)/$(TEST_OBJ)

# Remove test phony target before delivering the project
.PHONY: all clean fclean re test
