############  GNL TESTS  ############

SHELL		= /bin/sh

TEST_PROG	= test_suite

############  Compiler Config  ############

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCS		= -I$(INC_DIR)

############  Valgrind Config  ############

VG_LOG		= valgrind.log

VALGRIND	= valgrind -q --leak-check=full \
						  --show-leak-kinds=all \
						  --track-fds=yes \
						  --track-origins=yes \
						  --error-exitcode=42 \
						  --log-file=$(VG_LOG)

# --error-exitcode=42 lets us tell a valgrind error apart from a normal program error.

RED			= \033[0;31m
RESET		= \033[0m

# Check the previous command's exit code: 42 means valgrind found a leak/error
CHECK_VG	= ec=$$?; \
			if [ $$ec -eq 42 ]; then \
				printf "$(RED)LEAK ERROR: valgrind detected a memory leak or error$(RESET)\n"; \
				cat $(VG_LOG); rm -f $(VG_LOG); exit 1; \
			fi; \
			rm -f $(VG_LOG); \
			if [ $$ec -ne 0 ]; then exit $$ec; fi

############  Folders Config  ############

INC_DIR     = ..
SRC_DIR     = ..
OBJ_DIR     = obj

############  Files Config  ############

TEST_FILE	= test.c
ERR_FILE	= test_error.c
STDIN_FILE	= test_stdin.c
BONUS_FILE	= test_bonus.c

HEADER		= $(INC_DIR)/get_next_line.h

SRC_FILES	=	get_next_line.c \
				get_next_line_utils.c

# Bonus sources (must exist at the repo root before `make bonus` can link)
BONUS_SRC_FILES	=	get_next_line_bonus.c \
					get_next_line_utils_bonus.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
BONUS_SRCS	= $(addprefix $(SRC_DIR)/, $(BONUS_SRC_FILES))

# Inputs read by test.c (checked by diff_test.sh)
TEST_INPUTS	= inputs/test0.txt inputs/test_empty_file.txt inputs/test_one_line.txt inputs/test_only_nl.txt

# The three inputs read in parallel by the multi-fd bonus test
BONUS_INPUTS	= inputs/bonus_a.txt inputs/bonus_b.txt inputs/bonus_c.txt

############  Targets  ############

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(TEST_PROG): $(OBJS) $(TEST_FILE)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o $@

all: test

test: CFLAGS += -g3 -fsanitize=address -D BUFFER_SIZE=10
test: fclean $(TEST_PROG)
	./$(TEST_PROG) | cat -e

debug: CFLAGS += -g3 
debug: fclean $(OBJS) $(TEST_FILE)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o test_suite_debug

tester: fclean  $(OBJS) $(TEST_FILE)
	@echo "-- TESTER - memory checker: valgrind (leaks + errors + fds)"
	@echo "-- TESTER - BUFFER_SIZE=1"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=1 $(SRCS) $(TEST_FILE) $(INCS) -o tester-buf1
	@$(VALGRIND) ./tester-buf1 > /dev/null; $(CHECK_VG)
	@sh diff_test.sh 1 "$(TEST_INPUTS)"
	@echo "-- TESTER - BUFFER_SIZE=5"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=5 $(SRCS) $(TEST_FILE) $(INCS) -o tester-buf5
	@$(VALGRIND) ./tester-buf5 > /dev/null; $(CHECK_VG)
	@sh diff_test.sh 5 "$(TEST_INPUTS)"
	@echo "-- TESTER - BUFFER_SIZE=100"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=100 $(SRCS) $(TEST_FILE) $(INCS) -o tester-buf100
	@$(VALGRIND) ./tester-buf100 > /dev/null; $(CHECK_VG)
	@sh diff_test.sh 100 "$(TEST_INPUTS)"
	#@echo "-- TESTER - BUFFER_SIZE=1000000"
	#$(CC) $(CFLAGS) -D BUFFER_SIZE=1000000 $(OBJS) $(TEST_FILE) $(INCS) -o tester-buf1000000
	#@echo "not tested because it trigger a stack overflow (on purpose)"

errtest: fclean $(OBJS) $(ERR_FILE)
	@echo "-- ERRTEST - ERROR CASES (memory checker: valgrind)"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=1 $(SRCS) $(ERR_FILE) $(INCS) -o tester-error
	@echo "no access" > test_no_access_file.txt && chmod 000 test_no_access_file.txt
	@$(VALGRIND) ./tester-error; ec=$$?; rm -f test_no_access_file.txt; (exit $$ec); $(CHECK_VG)

stdin: fclean $(OBJS) $(STDIN_FILE)
	@echo "-- STDIN - interactive (Ctrl-D to quit)"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=42 $(SRCS) $(STDIN_FILE) $(INCS) -o stdin_test
	@./stdin_test
	@rm -f stdin_test

# Multi-fd bonus test. Requires the bonus sources at the repo root.
bonus: fclean
	@echo "-- BONUS - multi-fd (needs $(BONUS_SRC_FILES) at the repo root)"
	@$(CC) $(CFLAGS) -g3 -fsanitize=address -D BUFFER_SIZE=8 $(BONUS_SRCS) $(BONUS_FILE) $(INCS) -o bonus_test
	@./bonus_test
	@sh diff_test.sh bonus "$(BONUS_INPUTS)"
	@rm -rf bonus_test

memtest: fclean $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o mem_check
	@$(VALGRIND) ./mem_check > /dev/null 2>&1; $(CHECK_VG)
	@rm  -f ./mem_check

############  Cleaning  ############
clean:
	rm -f $(OBJS)

fclean: clean tclean

re: fclean all

tclean:
	rm -f $(TEST_PROG)
	rm -f $(TEST_PROG)_debug
	rm -rf output
	rm -f tester-buf*
	rm -f tester-error
	rm -f stdin_test
	rm -f bonus_test
	rm -f $(VG_LOG)
	rm -f test_no_access_file.txt


.PHONY: all clean fclean re test tester errtest stdin bonus tclean memtest
