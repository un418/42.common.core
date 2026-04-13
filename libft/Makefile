SHELL		= /bin/sh

NAME		= libft.a

TEST_FOLDER	= test
TEST_SRC	= test.c
TEST_OBJ	= test.o

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

HEADER		= libft.h

SRCS		= ft_isalpha.c

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
	rm -f $(TEST_OBJ)
	
re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS)  $(TEST_SRC) -L. -l:libft.a -o $(TEST_OBJ)
	./test.o

#$(CC) $(CFLAGS) -c $(TEST_FOLDER)/$(TEST_SRC) -L. -l:libft.a -o $(TEST_FOLDER)/$(TEST_OBJ)
#./$(TEST_FOLDER)/$(TEST_OBJ)

.PHONY: all clean fclean re test
