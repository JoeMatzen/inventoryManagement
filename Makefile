all:
	gcc -o project3 project3.c item.c sales.c

project3.o: project3.c item.o project3.h sales.o
	gcc -c project3.c item.o sales.o

item.o: item.c item.h
	gcc -c item.c

sales.o: sales.c sales.h
	gcc -c sales.c

clean:
	rm *.o
	
