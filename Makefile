SOURCES = src/*.c src/**/*.c
CFLAGS = -std=c23 -g3 -O0 -Wall -Wextra -Wpedantic
LDFLAGS = -lm

SOURCES = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/backend/operator/*.c)

default: build

install: build
	cp .build/calc /usr/local/bin

run: build
	./.build/clac

build: $(SOURCES)
	mkdir -p .build
	gcc $(CFLAGS) $(LDFLAGS) $(SOURCES) -o .build/clac

