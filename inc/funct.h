#ifndef FUNCT_H
#define FUNCT_H
#include "obj.h"
#include "struct.h"

Gamestate	*game(Ui *ui, Gamestate *gs);

  //game.c
ROOM	*movement(char key, vect *pos, ROOM *map);
ROOM	*teleport(vect *pos, ROOM *room, DOOR *d);

  //draw.c
int	print_centered(vect offset, char *s);//ret total offx
 //map
void	drawmap(vect pos, ROOM *map);
void	erasemap(vect pos, ROOM *map);
 //ui
void	refreshui(Ui *ui);
vect	drawmenu(const char *filename);//ret beg coord

  //load.c
Gamestate	*newgame(void);
 //gamestate
void	delgs(Gamestate *gs);
 //ui
Ui	*createui(void);
void	freeui(Ui *ui);
 //ROOM
ROOM	*loadroom(char *path);
void	delroom(ROOM *room);
 //save
void		save(Gamestate *gs);
Gamestate	*loadsave(void);

#endif
