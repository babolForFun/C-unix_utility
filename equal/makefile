equal: control.o doubleFile.o doubleFolder.o log.o main.o
	gcc -o equal control.o doubleFile.o doubleFolder.o log.o main.o
	cp /home/alan/Scrivania/equal/equal /bin/

control.o: control.c lib.h
	gcc -c control.c

doubleFile.o: doubleFile.c lib.h
	gcc -c doubleFile.c

doubleFolder.o: doubleFolder.c lib.h
	gcc -c doubleFolder.c

log.o: log.c lib.h
	gcc -c log.c

main.o: main.c lib.h
	gcc -c main.c