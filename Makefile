all: system
system: main.o LIST.o PCB.o
	gcc -o system main.o LIST.o PCB.o
main.o: main.c LIST.h PCB.h
	gcc -c -Wall main.c
PCB.o:	PCB.c PCB.h LIST.h
	gcc -c -Wall PCB.c
LIST.o: LIST.c LIST.h NODE.h
	gcc -c -Wall LIST.c
clean:
	rm -rf main.o PCB.o LIST.o system