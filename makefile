CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c99 -g

test: test.o lexer.o tokens.o string-auxiliar.o
	$(CC) $(CFLAGS) $^ -o $@

test.o: test.c lexer.h estructuras/tokens.h
	$(CC) $(CFLAGS) -c $<

lexer.o: lexer.c lexer.h estructuras/tokens.h estructuras/string-auxiliar.h
	$(CC) $(CFLAGS) -c $<

tokens.o: estructuras/tokens.c estructuras/tokens.h estructuras/string-auxiliar.h
	$(CC) $(CFLAGS) -c $<

string-auxiliar.o: estructuras/string-auxiliar.c estructuras/string-auxiliar.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o