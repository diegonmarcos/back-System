# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 09:31:09 by dinepomu          #+#    #+#              #
#    Updated: 2025/03/10 11:08:19 by dinepomu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# https://linktr.ee/diegonmarcos											   #
# **************************************************************************** #

# **************************************************************************** #
# **************************************************************************** #
NAME 	= pipex
VERBOSE = 0
MAKEFLAGS += --no-print-directory

# **************************************************************************** #
# **************************************************************************** #
CC 		= clang -g3
CFLAGS	= -Wall -Wextra 
RM		= rm -rf
AR		= ar rc

# **************************************************************************** #
# **************************************************************************** #
CINCLUDE	= -Iinc

# **************************************************************************** #
# **************************************************************************** #
SRCS_MAIN	=					\
			pipex.c				\
			1.ft_piping.c		\
			2.ft_execve.c		\
			3.error_handling.c	\

OBJS_1 = $(addprefix objs/, $(SRCS_MAIN:.c=.o))

SRCS_FILES	=

OBJS_2 = $(addprefix objs/, $(SRCS_FILES:.c=.o))

SRCS = $(SRCS_MAIN) $(SRCS_FILES)
OBJS = $(OBJS_1) $(OBJS_2)

VPATH	=						\
		src:					\
		src/pipes:				\
		src/shell:				\
		src/utils:

# **************************************************************************** #
# **************************************************************************** #
LIB1_DIR = libs/ft_mylib
LIB1_A = libs/ft_mylib/libft_mylib.a

# **************************************************************************** #
# **************************************************************************** #
all : $(NAME)

objs/%.o: %.c
	mkdir -p objs
	$(CC) $(CFLAGS) $(CINCLUDE) -c $< -o $@

$(LIB1_A):
	$(MAKE) -C $(LIB1_DIR)

$(NAME) : $(OBJS) $(LIB1_A)
	$(MAKE) folders
	$(CC) $(CFLAGS) $(CINCLUDE) $(OBJS) $(LIB1_A) -o $(NAME)


# **************************************************************************** #
# **************************************************************************** #
fclean : clean
	$(RM) $(NAME)
	$(RM) tests
	$(RM) objs
	$(RM) log
#	$(MAKE) fclean -C $(LIB1_DIR)

clean :
	$(RM) objs
#	$(MAKE) clean -C $(LIB1_DIR)

re : fclean all

bonus : clean
	$(MAKE) folders
	make -C src_bonus

ifeq ($(VERBOSE), 0)
.SILENT:
MAKEFLAGS += --no-print-directory
endif

folders:
	mkdir -p objs
	mkdir -p log/2.Memory_Check/allocs

# **************************************************************************** #
# **************************************************************************** #
test: fclean $(NAME)
	mkdir -p tests

	echo "\n### NORM ###"
	norminette src inc src_bonus | grep Error || true
	
	env > tests/infile
	
	echo "\n\n### VALGRIND ###"
	valgrind ./pipex tests/infile "grep -x "PATH=.*"" "cat" 2>&1 | grep "no leaks are possible" || true

	env | grep -x "PATH=.*" > tests/outfile_grep_cat.sys
	./pipex tests/infile "grep -x "PATH=.*"" "cat" tests/outfile_grep_cat.pipex

	env | grep -x "PATH=.*" | sed 's/.*PATH=//' > tests/outfile_grep_sed.sys
	./pipex tests/infile "grep -x "PATH=.*"" "sed s/.*PATH=//" tests/outfile_grep_sed.pipex

	echo "\n\n### TESTS ###"
	if [ "$$(cat tests/outfile_grep_cat.sys)" = "$$(cat tests/outfile_grep_cat.pipex)" ]; then echo "Test 1$(GREEN) OK$(RESET)"; else echo "$(RED)Test 1 FAILED$(RESET)"; fi
	if [ "$$(cat tests/outfile_grep_sed.sys)" = "$$(cat tests/outfile_grep_sed.pipex)" ]; then echo "Test 2$(GREEN) OK$(RESET)"; else echo "$(RED)Test 2 FAILED$(RESET)"; fi

test_bonus: fclean bonus
	mkdir -p tests

	echo "\n### NORM ###"
	norminette src inc src_bonus | grep Error || true

	
	env > tests/infile
	
	echo "\n\n### VALGRIND ###"
	valgrind ./pipex tests/infile "grep -x "PATH=.*"" "sed s/.*PATH=//" "sed s/:.*//"  2>&1 | grep "no leaks are possible" || true


	env | grep -x "PATH=.*" > tests/outfile_grep_cat.sys
	./pipex tests/infile "grep -x "PATH=.*"" "cat" tests/outfile_grep_cat.pipex

	env | grep -x "PATH=.*" | sed 's/.*PATH=//' > tests/outfile_grep_sed.sys
	./pipex tests/infile "grep -x "PATH=.*"" "sed s/.*PATH=//" tests/outfile_grep_sed.pipex

	env | grep -x "PATH=.*" | sed 's/.*PATH=//' | sed 's/:.*//' | sed 's/$$/\/CMD1/' > tests/outfile_grep_sed_cut.sys
	./pipex tests/infile "grep -x "PATH=.*"" "sed s/.*PATH=//" "sed s/:.*//" "sed s/$$/\/CMD1/" tests/outfile_grep_sed_cut.pipex

	echo "\n\n### TESTS ###"
	if [ "$$(cat tests/outfile_grep_cat.sys)" = "$$(cat tests/outfile_grep_cat.pipex)" ]; then echo "Test 1$(GREEN) OK$(RESET)"; else echo "$(RED)Test 1 FAILED$(RESET)"; fi
	if [ "$$(cat tests/outfile_grep_sed.sys)" = "$$(cat tests/outfile_grep_sed.pipex)" ]; then echo "Test 2$(GREEN) OK$(RESET)"; else echo "$(RED)Test 2 FAILED$(RESET)"; fi
	if [ "$$(cat tests/outfile_grep_sed_cut.sys)" = "$$(cat tests/outfile_grep_sed_cut.pipex)" ]; then echo "Test 3$(GREEN) OK$(RESET)"; else echo "$(RED)Test 2 FAILED$(RESET)"; fi

	






















# **************************************************************************** #
#                                DEFS/COLORS                               	   #
# **************************************************************************** #
DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
RESET =			\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m