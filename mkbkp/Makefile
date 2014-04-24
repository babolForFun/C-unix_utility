mkbkp: main.o doBkp2.o fun.h log.o showMyBkp.o exBkp.o
	gcc -o mkbkp main.o doBkp2.o log.o showMyBkp.o exBkp.o
	cp /home/alan/Scrivania/mkbkp/mkbkp /bin/


main.o: main.c fun.h
	gcc -c main.c

doBkp2.o: doBkp2.c fun.h
	gcc -c doBkp2.c

log.o: log.c fun.h
	gcc -c log.c

showMyBkp.o: showMyBkp.c fun.h
	gcc -c showMyBkp.c

exBkp.o: exBkp.c fun.h
	gcc -c exBkp.c