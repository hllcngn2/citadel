all:
	gcc src/*.c -o Citadel -l ncurses -I inc
clean:
	rm Citadel #-rf
debug:
	gcc debug.c src/maps.c -Iinc -lncurses -ocitadel_debug
