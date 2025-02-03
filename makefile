hendyMohamedA1: hendyMohamedA1.o hendyMohamedA1Main.o
	gcc hendyMohamedA1.o hendyMohamedA1Main.o -o hendyMohamedA1 -lm
hendyMohamedA1.o: hendyMohamedA1.c 
	gcc -Wall -std=c99 -c hendyMohamedA1.c
hendyMohamedA1Main.o: hendyMohamedA1Main.c 
	gcc -Wall -std=c99 -c hendyMohamedA1Main.c
clean:
	rm -f *.o hendyMohamedA1