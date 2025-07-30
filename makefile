CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c99

test: test.o tokenizer.o ast.o
	$(CC) -g -o $@ $^ $(CFLAGS)
	rm *.o

test.o: test.c tokenizer.h ast.h
	$(CC) -g -c $< $(CFLAGS)

tokenizer.o : tokenizer.c tokenizer.h
	$(CC) -g -c $< $(CFLAGS)

ast.o: ast.c ast.h tokenizer.h
	$(CC) -g -c $< $(CFLAGS)