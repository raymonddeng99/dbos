CC=gcc
AS=as
NAME=$(shell whoami)

CFLAGS=-std=gnu11 -Wall -O2 -fno-strict-aliasing

ifeq ($(SAN),1)
	CFLAGS += -fsanitize=address,undefined,leak
endif

all: example test1
test: test1
	./test1
test1: chloros.o swtch.o test1.o
	$(CC) $(CFLAGS) $^ -o $@
example: chloros.o swtch.o example.o
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.S
	$(AS) $< -o $@
clean:
	rm -f *.o test1 example *.tar.gz
format:
	clang-format -i *.c *.h
submit: clean
	tar -czf /tmp/lab1-$(NAME).tar.gz .
	mv /tmp/lab1-$(NAME).tar.gz .

.PHONY: clean format submit
