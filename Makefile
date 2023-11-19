all:
	gcc -o citadel		src/main1.c src/main2.c src/load.c src/game.c src/draw.c		-Iinc -lncurses
