src = main.c basic_shape.c chess_board.c chess_print.c chess_circle.c mouce.c desktop.c  server.c


para= -Wall
main:$(src)
	gcc -o main -lpthread $(src) $(para)
clean:
	-rm -rf main
	-rm -rf *.o
	-rm -rf *~
run:
	./main
	
	
