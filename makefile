
programa : main.o PaintGraph.o ReadFile_CreateGraph.o
	@gcc main.o PaintGraph.o ReadFile_CreateGraph.o -o programa

main.o : main.c ReadFile_CreateGraph.h PaintGraph.h
	@gcc -c main.c

PaintGraph.o : ReadFile_CreateGraph.h PaintGraph.h
	@gcc -c PaintGraph.c

ReadFile_CreateGraph.o : ReadFile_CreateGraph.h PaintGraph.h
	@gcc -c ReadFile_CreateGraph.c

clean:
	rm *.o programa