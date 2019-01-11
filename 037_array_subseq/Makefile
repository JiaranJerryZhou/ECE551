CFLAGS =-std=gnu99 -pedantic -Wall
maxSeq:maxSeq.o test-subseq.o
	gcc -o maxSeq maxSeq.o test-subseq.o
%.o:%.c
	gcc $(CFLAGS) -c $<
.PHONY:clean
clean:
	rm -f maxSeq *.o *.c~
	rm -f test-subseq *.o *.c~
