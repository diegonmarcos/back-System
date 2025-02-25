NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

SRCS = 	src/pipex.c\
		src/utils.c\
		libft/libft.a\

SRCS_BONUS = 	src_bonus/pipex_bonus.c\
				src_bonus/utils_bonus.c\
				libft/libft.a\

$(NAME) :
	make all -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all

bonus : clean
	make all -C libft
	gcc $(CFLAGS) $(SRCS_BONUS) -o $(NAME)

test: $(NAME)
	rm -rf tests
	mkdir -p tests
	echo "HELLO WORLD from 42\nTest for Pipex 21\n#Thank you\n" > infile.test
	./pipex infile.test "cat" "wc -l" outfile1.test
	./pipex infile.test "cat" "grep 42" outfile2.test
	./pipex infile.test "cat" "grep Thank" outfile3.test
	./pipex infile.test "cat" "tr A-Z a-z" outfile4.test
	echo "\n\n### Results ###"
	if [ "$$(cat outfile1.test)" = "4" ]; then echo "Test 1$(GREEN) OK$(RESET)"; else echo "$(RED)Test 1 FAILED"; fi
	if [ "$$(cat outfile2.test)" = "HELLO WORLD from 42" ]; then echo "Test 2$(GREEN) OK$(RESET)"; else echo "$(RED)Test 2 FAILED"; fi
	if [ "$$(cat outfile3.test)" = "#Thank you" ]; then echo "Test 3$(GREEN) OK$(RESET)"; else echo "$(RED)Test 3 FAILED"; fi
	expected_output=$(printf "hello world from 42\ntest for pipex 21\n#thank you")
	if [ "$$(cat outfile4.test)" = "$$expected_output" ]; then echo "Test$(GREEN) 4 OK$(RESET)"; else echo "$(RED)Test 4 FAILED$(RESET)"; fi
	mv *.test tests