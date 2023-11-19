#include "obj.h"
#include "struct.h"
#include "funct.h"
#include "def.h"
#include "macro.h"
#include <ncurses.h>

Gamestate	*game(Ui *ui, Gamestate *gs){
vect	 pos	=gs->pos;	//I'm still not sure that
ROOM	*room	=gs->room;	//I'll need to pass gs
				//at any point
char	k =0;			//todo: pack/unpack()
do {


switch(k) {	//todo: escape keys support
case K_SAVE:
	gs->pos		=pos;
	gs->room	=room;
	save(gs); break;
case K_UP:
case K_DOWN:
case K_LEFT:
case K_RIGHT:
case K_UP_LEFT:
case K_UP_RIGHT:
case K_DOWN_LEFT:
case K_DOWN_RIGHT:
	room =movement(k, &pos, room); break;
default:break;}

//  displaying
drawmap(pos, room);
mvaddch(MID_Y,MID_X, gs->char_symbol);

box(ui->w_dialog, 0, 0);
refreshui(ui);


} while((k =getch()) !=27);
gs->pos		=pos;
gs->room	=room;
return gs;}
