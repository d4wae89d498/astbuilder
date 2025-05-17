all: test

test: 
	clang -Isrc test.c && ./a.out

clean:
	rm a.out