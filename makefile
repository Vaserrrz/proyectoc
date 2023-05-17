OUTPUT = programa.exe
programa:
	gcc -o programa main.c PaintGraph.c ReadFile_CreateGraph.c -I.

all:programa

run: programa
	./${OUTPUT}

clean:
	del ${OUTPUT}

