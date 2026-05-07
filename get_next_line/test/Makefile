SHELL		= /bin/sh

NAME		= gnl_prog

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
HEADER		= $(INC_DIR)/get_next_line.h

INC_DIR     = ..
SRC_DIR     = ..
OBJ_DIR     = obj

SRC_FILES	=	get_next_line.c \
				get_next_line_utils.c


SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INCS		= -I$(INC_DIR)


## Tests
TEST_PROG	= gnl_test_suite
TEST_FILE	= test.c


all: test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(TEST_PROG): $(OBJS) $(TEST_FILE)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o $@

test: CFLAGS += -g3 -fsanitize=address
test: $(TEST_PROG)
	./$(TEST_PROG)

debug: CFLAGS += -g3 
debug: $(TEST_PROG)

clean:
	rm -f $(OBJS)

fclean: clean tclean

re: fclean all

#####################

# tester: re
# 	$(CC) $(CFLAGS) $(TEST_FILE) $(INCS) -o tester
# 	./tester > difftester.log 
# 	./tester.sh

tclean:
	rm -f $(TEST_PROG)
# 	rm -f tester
# 	rm -f difftester.log 
# 	rm -f difftest_ft_printf.txt
# 	rm -f difftest_printf.txt


memtest: fclean
	@$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o mem_check
	@valgrind	--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				./test/mem_check > /dev/null
	@rm  -f ./test/mem_check

.PHONY: all clean fclean re test tclean memtest
