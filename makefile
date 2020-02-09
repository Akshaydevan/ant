all: ant

ant: 	txt.o memory.o paint.o getkey.o
	gcc txt.o memory.o paint.o getkey.o -o ant

txt.o:	txt.c
	gcc -c txt.c 

getkey.o:txt.c
	gcc -c getkey.c 

memory.o:txt.c
	gcc -c memory.c 

paint.o:txt.c
	gcc -c paint.c  


