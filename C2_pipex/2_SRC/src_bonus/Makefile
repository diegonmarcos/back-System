# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 09:31:09 by dinepomu          #+#    #+#              #
#    Updated: 2025/02/12 11:30:09 by dinepomu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# **************************************************************************** #
NAME 	= ../pipex
VERBOSE = 0

# **************************************************************************** #
# **************************************************************************** #
CC 		= clang -g
CFLAGS	= -Werror -Wall -Wextra 
RM		= rm -rf
AR		= ar rc

# **************************************************************************** #
# **************************************************************************** #
CINCLUDE	= -Iinclude -I../include

# **************************************************************************** #
# **************************************************************************** #
SRCS_MAIN	=						\
		pipex_bonus.c				\
		1.ft_piping_bonus.c			\
		1.ft_piping_heredoc_bonus.c	\
		3.error_handling_bonus.c		

OBJS_1 = $(addprefix objs/, $(SRCS_MAIN:.c=.o))

SRCS_FILES	=			\
		2.ft_execve.c	\

OBJS_2 = $(addprefix objs/, $(notdir $(SRCS_FILES:.c=.o)))

#SRCS_LIBS = ../libs/libft_mylib.a

SRCS = $(SRCS_MAIN) $(SRCS_FILES)
OBJS = $(OBJS_1) $(OBJS_2) $(SRCS_LIBS)

VPATH	=				\
		src/main:			\
		src/pipes:			\
		src/utils:			\
		../src/shell:	


# **************************************************************************** #
# **************************************************************************** #
LIB1_DIR = ../libs/ft_mylib
LIB1_A = ../libs/libft_mylib.a

# **************************************************************************** #
# **************************************************************************** #
all : $(NAME)

objs/%.o: %.c
	mkdir -p objs
	$(CC) $(CFLAGS) $(CINCLUDE) -c $< -o $@

$(LIB1_A):
#	$(MAKE) -C $(LIB1_DIR)

$(NAME) : $(OBJS) $(LIB1_A)
	$(CC) $(CFLAGS) $(CINCLUDE) $(OBJS) $(LIB1_A) -o $(NAME)


# **************************************************************************** #
# **************************************************************************** #
fclean : clean
	$(RM) $(NAME)
	$(RM) tests
#	$(MAKE) fclean -C $(LIB1_DIR)

clean :
	$(RM) $(OBJS)
#	$(MAKE) clean -C $(LIB1_DIR)

re : fclean all

ifeq ($(VERBOSE), 0)
.SILENT:
endif

# **************************************************************************** #
# **************************************************************************** #
test: $(NAME)
	mkdir -p tests
	valgrind ./pipex infile.test "cat" "wc -l" || true

	echo "HELLO WORLD from 42\nTest for Pipex 21\n#Thank you\n" > tests/infile

	< tests/infile ls -l | wc -l > tests/outfile_ls_wc.sys
	./pipex tests/infile "ls -l" "wc -l" tests/outfile_ls_wc.pipex

	< tests/infile grep a1 | wc -w > tests/outfile_grep_wc.sys
	./pipex tests/infile "grep a1" "wc -w" tests/outfile_grep_wc.pipex

	echo "\n\n### RESULTS ###"
	if [ "$$(cat tests/outfile_ls_wc.sys)" = "$$(cat tests/outfile_ls_wc.pipex)" ]; then echo "Test 1$(GREEN) OK$(RESET)"; else echo "$(RED)Test 1 FAILED$(RESET)"; fi
	if [ "$$(cat tests/outfile_grep_wc.sys)" = "$$(cat tests/outfile_grep_wc.pipex)" ]; then echo "Test 2$(GREEN) OK$(RESET)"; else echo "$(RED)Test 2 FAILED$(RESET)"; fi


test_bonus:
	mkdir -p tests
	echo "HELLO WORLD from 42\nTest for Pipex 21\n#Thank you\n" > tests/infile

	< tests/infile ls -l | wc -l > tests/outfile_bonus_ls_wc.sys
	./pipex tests/infile "ls -l" "wc -l" tests/outfile_bonus_ls_wc.pipex

	echo "#!/bin/bash\n\
	cat <<EOF | tee tests/input.txt | grep 'pattern' | sort | uniq | wc -l > tests/outfile_bonus_heredoc.sys\n\
	This is a line with pattern.\n\
	This line does not match.\n\
	Another line with pattern.\n\
	Yet another line with pattern.\n\
	EOF" > tests/test_heredoc.sh
	chmod +x tests/test_heredoc.sh && ./tests/test_heredoc.sh
	./pipex tests/input.txt "grep 'pattern'" "sort" "uniq" "wc -l" tests/outfile_bonus_heredoc.pipex

	echo "\n\n### RESULTS ###"
	if [ "$$(cat tests/outfile_bonus_ls_wc.sys)" = "$$(cat tests/outfile_bonus_ls_wc.pipex)" ]; then echo "Test 3$(GREEN) OK$(RESET)"; else echo "$(RED)Test 3 FAILED$(RESET)"; fi
	if [ "$$(cat tests/outfile_bonus_heredoc.sys)" = "$$(cat tests/outfile_bonus_heredoc.pipex)" ]; then echo "Test 4$(GREEN) OK$(RESET)"; else echo "$(RED)Test 4 FAILED$(RESET)"; fi

	













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