P = src/c
SRC = $(P)/abstract.c \
      $(P)/geometry.c \
      $(P)/io.c \
      $(P)/models.c
CFLAGS = -lm
TESTS = tests/tests.c

build :
	cc $(CFLAGS) $(SRC) $(P)/main.c -o bin/main
run : 
	cc $(CFLAGS) $(SRC) $(P)/main.c -o bin/main
	bin/main
clean :
	rm bin/* tmp/*
test :
	cc $(CFLAGS) $(SRC) $(TESTS) -o bin/run_tests
	bin/run_tests	
