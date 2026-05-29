SHELL		= /bin/sh

# ─── Output ──────────────────────────────────────────────────────────────────

NAME		= libftprintf.a

# ─── Compiler ────────────────────────────────────────────────────────────────

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# ─── Directories ─────────────────────────────────────────────────────────────

INC_DIR		= inc
SRC_DIR		= src
OBJ_DIR		= obj
TEST_DIR	= test

# ─── Sources ─────────────────────────────────────────────────────────────────

SRC_FILES	=	ft_printf.c \
				ft_printf_ascii.c \
				ft_printf_num.c

HEADERS		= $(INC_DIR)/ft_printf.h $(SRC_DIR)/ft_printf_private.h
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ─── Build ────────────────────────────────────────────────────────────────────

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean tclean
	rm -f $(NAME)

re: fclean all

# ─── Tests ───────────────────────────────────────────────────────────────────

TEST_PROG	= test_suite
TEST_FILE	= test.c
INCS		= -I$(INC_DIR)
LIBS		= -L. -lftprintf

test: CFLAGS += -g3 -fsanitize=address
test: re
	$(CC) $(CFLAGS) $(TEST_DIR)/$(TEST_FILE) $(INCS) $(LIBS) -o $(TEST_DIR)/$(TEST_PROG)
	./$(TEST_DIR)/$(TEST_PROG)

# -Werror removed to allow testing undefined behaviour
test_ub: CFLAGS = -Wall -Wextra -g3
test_ub: re
	$(CC) $(CFLAGS) $(TEST_DIR)/ub_test.c $(INCS) $(LIBS) -o $(TEST_DIR)/ub_test
	./$(TEST_DIR)/ub_test

tester: re
	$(CC) $(CFLAGS) $(TEST_DIR)/$(TEST_FILE) $(INCS) $(LIBS) -o $(TEST_DIR)/tester
	./$(TEST_DIR)/tester > $(TEST_DIR)/difftester.log
	./$(TEST_DIR)/tester.sh

memtest: re
	@$(CC) $(CFLAGS) $(TEST_DIR)/$(TEST_FILE) $(INCS) $(LIBS) -o $(TEST_DIR)/mem_check
	@valgrind	--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				./test/mem_check > /dev/null
	@rm -f ./test/mem_check

tclean:
	rm -f $(TEST_DIR)/$(TEST_PROG)
	rm -f $(TEST_DIR)/tester
	rm -f $(TEST_DIR)/difftester.log
	rm -f $(TEST_DIR)/difftest_ft_printf.txt
	rm -f $(TEST_DIR)/difftest_printf.txt
	rm -f $(TEST_DIR)/ub_test

# ─────────────────────────────────────────────────────────────────────────────

.PHONY: all clean fclean re test tclean memtest
