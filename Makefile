SOURCES = src/main.c src/args.c src/lexer.c src/interpreter.c src/stack.c
CFLAGS = -std=c23 -g3 -O0 -Wall -Wextra -Wpedantic -Werror
LDFLAGS = -lm

default: build

install: build
	cp .build/calc /usr/local/bin

run: build
	./.build/rpn

build: $(SOURCES)
	mkdir -p .build
	gcc $(CFLAGS) $(LDFLAGS) $(SOURCES) -o .build/clac

