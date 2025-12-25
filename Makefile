PROJECT_NAME = ConsoleApplication
C_FILES = $(wildcard src/*.c)
O_FILES = $(patsubst %.c, %.o, $(C_FILES))


ALL_O_FILES = $(O_FILES) main.o

ConsoleApplication : $(ALL_O_FILES)
	g++ -Wall -Wextra -pedantic -g -fsanitize=address,undefined $(ALL_O_FILES) -o $(PROJECT_NAME)

main.o : main.c
	g++ -Wall -Wextra -pedantic -g -fsanitize=address,undefined -c  main.c -o main.o

%.o : %.c
	g++ -Wall -Wextra -pedantic -g -fsanitize=address,undefined -c $< -o $@

clean :
	rm -f $(PROJECT_NAME) $(O_FILES) main.o
