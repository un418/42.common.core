SHELL		= /bin/sh

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
HEADER		= $(INC_DIR)/ft_printf.h

INC_DIR     = inc
SRC_DIR     = src
OBJ_DIR     = obj

SRC_FILES	=	ft_printf.c \
				ft_printf_ascii.c \
				ft_printf_num.c


# OBJS		= $(SRCS:.c=.o)

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))


## Libft
LIBFT_DIR	= ../libft
LIBFT		= $(LIBFT_DIR)/libft.a

## Tests
TEST_DIR	= test
TEST_PROG	= test_suite
TEST_FILE	= test.c

INCS		= -I$(INC_DIR) -I$(LIBFT_DIR)
LIBS		= -L. -lftprintf -L$(LIBFT_DIR) -lft

all: $(NAME) $(LIBFT)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean tclean
	rm -f $(NAME)

re: fclean all

#####################

$(LIBFT):
	make -C $(LIBFT_DIR)

test: CFLAGS += -g3 -fsanitize=address
test: re
	$(CC) $(CFLAGS) $(TEST_DIR)/$(TEST_FILE) $(INCS) $(LIBS) -o $(TEST_DIR)/$(TEST_PROG)
	./$(TEST_DIR)/$(TEST_PROG)

tester: re
	$(CC) $(CFLAGS) $(TEST_DIR)/$(TEST_FILE) $(INCS) $(LIBS) -o $(TEST_DIR)/tester
	./$(TEST_DIR)/tester > tester.log 
	./$(TEST_DIR)/tester.sh

tclean:
	rm -f $(TEST_DIR)/$(TEST_PROG)
	rm -f $(TEST_DIR)/tester
	rm -f $(TEST_DIR)/difftest_ft_printf.txt
	rm -f $(TEST_DIR)/difftest_printf.txt


memtest: re
	@$(CC) $(CFLAGS) $(TEST_DIR)/$(TEST_FILE) $(INCS) $(LIBS) -o $(TEST_DIR)/mem_check
	@valgrind	--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				./test/mem_check > /dev/null
	@rm  -f ./test/mem_check

.PHONY: all clean fclean re test tclean
