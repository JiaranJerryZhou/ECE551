SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRCS))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98
myShell: $(OBJS)
	g++ $(CPPFLAGS) -o myShell $(OBJS)
%.o: %.cpp
	g++ $(CPPFLAGS) -c $<
.PHONY: clean
clean:
	rm myShell *~ *.o
