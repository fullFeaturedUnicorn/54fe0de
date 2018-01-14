P = src/c
SRC = $(P)/abstract.c \
      $(P)/geometry.c \
      $(P)/io.c \
      $(P)/models.c \
      $(P)/main.c 
CFLAGS = -lm
TESTS = tests/tests.c

build :
	cc $(CFLAGS) $(SRC) -o bin/main
clean :
	rm bin/* tmp/*
test :
