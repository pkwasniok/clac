SOURCES = src/main.c
CFLAGS = -g3 -O0

default: build

run: build
	./.build/rpn

build: $(SOURCES)
	mkdir -p .build
	gcc $(CFLAGS) $(SOURCES) -o .build/rpn

