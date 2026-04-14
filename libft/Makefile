SHELL		= /bin/sh

NAME		= libft.a

TEST_FOLDER	= test
TEST_SRC	= test.c
TEST_OBJ	= test.o

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

HEADER		= libft.h

SRCS		=	ft_isalpha.c	\
				ft_isdigit.c	\
				ft_isalnum.c	\
				ft_isascii.c	\
				ft_isprint.c	\
				ft_strlen.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME) test

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
# To remove before delivering the project
	rm -f $(TEST_OBJ) 
	
re: fclean all

# To remove before delivering the project
test: $(NAME)
	$(CC) $(CFLAGS)  $(TEST_SRC) -L. -l:libft.a -o $(TEST_OBJ)
	./test.o

# Find out why it don't work in another folder #TODO
#$(CC) $(CFLAGS) -c $(TEST_FOLDER)/$(TEST_SRC) -L. -l:libft.a -o $(TEST_FOLDER)/$(TEST_OBJ)
#./$(TEST_FOLDER)/$(TEST_OBJ)

# Remove test phony target before delivering the project
.PHONY: all clean fclean re test
