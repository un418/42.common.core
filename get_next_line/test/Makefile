############  GNL TESTS  ############

SHELL		= /bin/sh

TEST_PROG	= test_suite

############  Compiler Config  ############

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCS		= -I$(INC_DIR)

############  Folders Config  ############

INC_DIR     = ..
SRC_DIR     = ..
OBJ_DIR     = obj

############  Files Config  ############

TEST_FILE	= test.c

HEADER		= $(INC_DIR)/get_next_line.h

SRC_FILES	=	get_next_line.c \
				get_next_line_utils.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

############  Targets  ############

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(TEST_PROG): $(OBJS) $(TEST_FILE)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o $@

all: test

test: CFLAGS += -g3 -fsanitize=address
test: fclean $(TEST_PROG)
	./$(TEST_PROG) | cat -e

debug: CFLAGS += -g3 
debug: fclean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o test_suite_debug

# tester: fclean
# 	$(CC) $(CFLAGS) $(TEST_FILE) $(INCS) -o tester
# 	./tester > difftester.log 
# 	./tester.sh

memtest: fclean $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o mem_check
	@valgrind	--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				./test/mem_check > /dev/null
	@rm  -f ./test/mem_check

memtestmac: fclean $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o mem_check
	leaks --atExit -- ./mem_check
	@rm  -f ./mem_check

############  Cleaning  ############
clean:
	rm -f $(OBJS)

fclean: clean tclean

re: fclean all

tclean:
	rm -f $(TEST_PROG)
	rm -f $(TEST_PROG)_debug
# 	rm -f tester
# 	rm -f difftester.log 
# 	rm -f difftest_ft_printf.txt
# 	rm -f difftest_printf.txt



.PHONY: all clean fclean re test tclean memtest
