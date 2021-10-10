.PHONY:clean

OBJS=main.o Start.o sudoku.o Global.o
CC = g++

main:$(OBJS)
%.o:%.cpp
	$(CC) $^ -g -c -lstdc++ -o $@

clean:
	-rm -rf $(OBJS) main