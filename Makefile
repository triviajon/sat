# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude -g

# Source directories
SRCDIR = src
TESTDIR = tests

# Object files
TEST_OBJS = $(TESTDIR)/tester.o $(TESTDIR)/test_eval_CNFSatFormula.o $(TESTDIR)/test_solve_CNFSatFormula.o
MAIN_OBJS = $(SRCDIR)/main.o
SHARED_OBJS = $(SRCDIR)/var_map.o $(SRCDIR)/sat.o $(SRCDIR)/parse.o $(SRCDIR)/solve.o

# Executable names
MAIN_EXE = sat
TEST_EXE = sat_tester

# Conditional rules based on TEST variable
ifeq ($(TEST), 1)
all: $(TEST_EXE)
OBJS = $(SHARED_OBJS) $(TEST_OBJS)
else
all: $(MAIN_EXE)
OBJS = $(SHARED_OBJS) $(MAIN_OBJS)
endif

# Rule to build the main executable
$(MAIN_EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build the test executable
$(TEST_EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Generic rule to compile C files to object files from src directory
$(SRCDIR)/%.o: $(SRCDIR)/%.c include/*.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Generic rule to compile C files to object files from tests directory
$(TESTDIR)/%.o: $(TESTDIR)/%.c include/*.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(SRCDIR)/*.o $(TESTDIR)/*.o $(MAIN_EXE) $(TEST_EXE)
