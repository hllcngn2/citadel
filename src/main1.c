#include "struct.h"
#include "funct.h"
#include <ncurses.h>

int	main(int ac, char **av){
initscr(); cbreak(); noecho();
curs_set(0); //nodelay(stdscr, true);
//refresh();

//loading game elements
Gamestate	*gs =loadsave();
if (!gs){//title screen
	vect toclr =drawmenu("000");
	if (getch() ==27){ endwin(); return 0;}//quit in the title screen
	move(toclr.y,toclr.x); clrtobot();
	gs =newgame();}
if (!gs){ endwin(); return 0;}//quit in the nick screen

//creating interface
Ui	*ui =createui();
mvprintw(1,COLS-15, "%s", gs->nick);	//todo: player window
mvwprintw(ui->w_title, 1,4, gs->room->title);

//game
gs =game(ui, gs);

//saving
save(gs);

delgs(gs);
freeui(ui); endwin();
return 0;}
