############  GNL TESTS  ############

SHELL		= /bin/sh

TEST_PROG	= test_suite

############  Compiler Config  ############

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -D OUTPUT_DIR='"$(OUT_DIR)"'
INCS		= -I$(INC_DIR)

############  Valgrind Config  ############

VG_LOG		= valgrind.log

VALGRIND	= valgrind -q --leak-check=full \
						  --show-leak-kinds=all \
						  --track-fds=yes \
						  --track-origins=yes \
						  --error-exitcode=42 \
						  --log-file=$(VG_LOG)
# -q + --log-file send valgrind's report to a file instead of the terminal, so the
# tested program's own output can be silenced without hiding valgrind.
# --error-exitcode=42 lets us tell a valgrind error apart from a normal program error.

RED			= \033[0;31m
RESET		= \033[0m

# Check the previous command's exit code: 42 means valgrind found a leak/error
# (see --error-exitcode above). Only then do we print its report (from the log)
# and a banner. Any other non-zero code is propagated as-is.
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
OUT_DIR     = output

############  Files Config  ############

TEST_FILE	= test.c
ERR_FILE	= test_error.c
STDIN_FILE	= test_stdin.c

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

test: CFLAGS += -g3 -fsanitize=address -D BUFFER_SIZE=10
test: fclean $(TEST_PROG)
	./$(TEST_PROG) | cat -e

debug: CFLAGS += -g3 
debug: fclean $(OBJS) $(TEST_FILE)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o test_suite_debug

tester: fclean  $(OBJS) $(TEST_FILE)
	@echo "-- TESTER - BUFFER_SIZE=1"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=1 $(SRCS) $(TEST_FILE) $(INCS) -o tester-buf1
	@$(VALGRIND) ./tester-buf1 > /dev/null 2>&1; $(CHECK_VG)
	@sh diff_test.sh 1 $(OUT_DIR)
	@echo "-- TESTER - BUFFER_SIZE=5"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=5 $(SRCS) $(TEST_FILE) $(INCS) -o tester-buf5
	@$(VALGRIND) ./tester-buf5 > /dev/null 2>&1; $(CHECK_VG)
	@sh diff_test.sh 5 $(OUT_DIR)
	@echo "-- TESTER - BUFFER_SIZE=100"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=100 $(SRCS) $(TEST_FILE) $(INCS) -o tester-buf100
	@$(VALGRIND) ./tester-buf100 > /dev/null 2>&1; $(CHECK_VG)
	@sh diff_test.sh 100 $(OUT_DIR)
	#@echo "-- TESTER - BUFFER_SIZE=1000000"
	#$(CC) $(CFLAGS) -D BUFFER_SIZE=1000000 $(OBJS) $(TEST_FILE) $(INCS) -o tester-buf1000000
	#@echo "not tested because it trigger a stack overflow (on purpose)"

errtest: fclean $(OBJS) $(ERR_FILE)
	@echo "-- ERRTEST - ERROR CASES"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=1 $(SRCS) $(ERR_FILE) $(INCS) -o tester-error
	@echo "no access" > test_no_access_file.txt && chmod 000 test_no_access_file.txt
	@$(VALGRIND) ./tester-error; ec=$$?; rm -f test_no_access_file.txt; (exit $$ec); $(CHECK_VG)

stdin: fclean $(OBJS) $(STDIN_FILE)
	@echo "-- STDIN - interactive (Ctrl-D to quit)"
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=42 $(SRCS) $(STDIN_FILE) $(INCS) -o stdin_test
	@./stdin_test
	@rm -f stdin_test

memtest: fclean $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(TEST_FILE) $(INCS) -o mem_check
	@$(VALGRIND) ./mem_check > /dev/null 2>&1; $(CHECK_VG)
	@rm  -f ./mem_check

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
	rm -rf $(OUT_DIR)
	rm -f tester-buf*
	rm -f tester-error
	rm -f stdin_test
	rm -f $(VG_LOG)
	rm -f test_no_access_file.txt


.PHONY: all clean fclean re test tester errtest stdin tclean memtest
