woolfy : main.o game.o event.o draw.o
	gcc -o woolfy main.o game.o event.o draw.o -lSDL -lm -std=c99

game.o : game.c game.h
	gcc -c game.c -lSDL -lm -std=c99

event.o : event.c event.h
	gcc -c event.c -lSDL -std=c99

draw.o : draw.c draw.h
	gcc -c draw.c -lSDL -std=c99

main.o : main.c
	gcc -c main.c -lSDL -std=c99

