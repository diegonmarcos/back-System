# PIPEX


## Compiling
``` bash
make
```
## Usage
### pipex
```
./pipex <infile> <cmd1> <cmd2> <outfile>
```

### pipex_bonus  
 ```
./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>
```

```
./pipex here_doc <limiter> <cmd1> <cmd2> <cmd3> ... <outfile>
```

## tests
```sh
\
###################
#File Creation
mkdir -p tests
echo -e "HELLO WORLD from 42\nTest for Pipex 21\n#Thank you\n" > infile.test; \
###################
#Teste1
	./pipex infile.test "cat" "wc -l" outfile1.test; \
#Teste2
	./pipex infile.test "cat" "grep 42" outfile2.test; \
#Test3
	./pipex infile.test "cat" "grep Thank" outfile3.test; \
#Test4
	./pipex infile.test "cat" "tr A-Z a-z" outfile4.test; \
###################
echo "\n\n### Results ###";\
if [ "$(cat outfile1.test)" = "4" ]; then echo "Test 1 OK"; else echo "Test 1 FAILED"; fi; \
if [ "$(cat outfile2.test)" = "HELLO WORLD from 42" ]; then echo "Test 2 OK"; else echo "Test 2 FAILED"; fi;\
if [ "$(cat outfile3.test)" = "#Thank you" ]; then echo "Test 3 OK"; else echo "Test 3 FAILED"; fi;\
expected_output=$(printf "hello world from 42\ntest for pipex 21\n#thank you")
if [ "$(cat outfile4.test)" = "$expected_output" ]; then echo "Test 4 OK"; else echo "Test 4 FAILED"; fi
mv *.test tests
```



## Feautures Implementation and Fixes


# Resources
### Search Files
env | grep PATH  > outfile
env | grep -x "PATH=.*"  > example


