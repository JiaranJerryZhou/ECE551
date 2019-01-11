CFLAGS=-std=gnu99 -pedantic -Wall
myProgram: power.o test-power.o
	gcc -o myProgram power.o test-power.o
%.o: %.c
	gcc $(CFLAGS) -c $<
.PHONY: clean
clean:
	rm -f power.o test-power.o
